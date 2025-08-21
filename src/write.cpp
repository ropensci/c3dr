#include <Rcpp.h>
#include "ezc3d/ezc3d_all.h"

// [[Rcpp::export]]
bool write(Rcpp::List object, const std::string &filepath) {
  // create empty c3d object
  ezc3d::c3d c3d;
  Rcpp::List p = object["parameters"];
  Rcpp::CharacterVector gnames = p.names();

  // write parameters
  // loop over each group
  for (int i = 0; i < p.size(); ++i) {
    Rcpp::List l = p[i];
    std::string gname = Rcpp::as<std::string>(gnames[i]);
    Rcpp::CharacterVector pnames = l.names();
    // loop over each parameter inside a group
    for (int j = 0; j < l.size(); ++j) {
      std::string pname = Rcpp::as<std::string>(pnames[j]);
      ezc3d::ParametersNS::GroupNS::Parameter param(pname);
      Rcpp::RObject value = l[j];
      std::vector<size_t> dim = {};
      if (Rcpp::is<Rcpp::List>(value)) {
        // if parameter value is a list
        // this means that the parameter has three dimensions (row, col, sheet)
        // currently only double type values are supported, but I haven't seen
        // any other yet.
        Rcpp::List ml = l[j];
        std::vector<double> flatVec;
        // write empty entry when list is empty
        if (ml.size() == 0) {
          param.set(flatVec, {0,0,0});
        } else {
          // flatten vector
          for (int k = 0; k < ml.size(); ++k) {
            Rcpp::NumericMatrix m = ml[k];
            flatVec.insert(flatVec.end(), m.begin(), m.end());
          }
          // set dimensions based on the first matrix
          // assuming all matrices have the same dimension
          Rcpp::NumericMatrix m = ml[0];
          Rcpp::IntegerVector dimv = m.attr("dim");
          dim = {static_cast<size_t>(dimv[0]), static_cast<size_t>(dimv[1]), static_cast<size_t>(ml.size())};
          param.set(flatVec, dim);
        }
      } else if (Rf_isMatrix(value)) {
        // if parameter value is a matrix
        // this means that the parameter is two dimensions (row, col)
        Rcpp::IntegerVector dimv(Rf_getAttrib(value, R_DimSymbol));
        dim = {static_cast<size_t>(dimv[0]), static_cast<size_t>(dimv[1])};
        // check if the matrix is integer or numeric
        if (Rf_isInteger(value)) {
          Rcpp::IntegerVector iv = Rcpp::as<Rcpp::IntegerVector>(value);
          std::vector<int> intvec(iv.begin(), iv.end());
          param.set(intvec, dim);
        } else if (Rf_isReal(value)) { // double (numeric)
          Rcpp::NumericVector nv = Rcpp::as<Rcpp::NumericVector>(value);
          std::vector<double> numvec(nv.begin(), nv.end());
          param.set(numvec, dim);
        }
      } else if (Rf_isInteger(value)) {
        Rcpp::IntegerVector intValue = Rcpp::as<Rcpp::IntegerVector>(value);
        std::vector<int> intvec(intValue.begin(), intValue.end());
        param.set(intvec);
      } else if (Rf_isNumeric(value)) {
        Rcpp::NumericVector numericValue = Rcpp::as<Rcpp::NumericVector>(value);
        std::vector<double> numvec(numericValue.begin(), numericValue.end());
        param.set(numvec);
      } else if (Rf_isString(value) || Rf_isString(Rcpp::wrap(value))) {
        // Handle string or vector of strings
        if (Rcpp::is<Rcpp::CharacterVector>(value)) {
          Rcpp::CharacterVector charVec = Rcpp::as<Rcpp::CharacterVector>(value);
          std::vector<std::string> strvec(charVec.size());
          for (int k = 0; k < charVec.size(); ++k) {
            strvec[k] = Rcpp::as<std::string>(charVec[k]);
          }
          param.set(strvec);
        } else {
          std::string strValue = Rcpp::as<std::string>(value);
          param.set(std::vector<std::string>{strValue});
        }
      } else if (Rf_isLogical(value)) {
        bool boolValue = Rcpp::as<bool>(value);
        param.set(boolValue);
      } else {
        Rcpp::Rcerr << "Error: Unsupported parameter type for '" << pname << "'." << std::endl;
        return false;
      }

      c3d.parameter(gname, param);
    }

  }

  // write c3dr related parameters to the EZC3D group
  ezc3d::ParametersNS::GroupNS::Parameter pc3dr("BINDING");
  pc3dr.set("c3dr");
  c3d.parameter("EZC3D", pc3dr);
  ezc3d::ParametersNS::GroupNS::Parameter pc3drversion("C3DR_VERSION");
  pc3drversion.set("0.2.0");
  c3d.parameter("EZC3D", pc3drversion);

  // write point and analog data
  Rcpp::List data = object["data"];
  Rcpp::List analog = object["analog"];
  Rcpp::NumericMatrix rdata = object["residuals"];

  for (int iframe = 0; iframe < data.size(); ++iframe) {
    Rcpp::List fdata = data[iframe];
    Rcpp::NumericMatrix adata = analog[iframe];
    ezc3d::DataNS::Frame f;

    // set point data
    ezc3d::DataNS::Points3dNS::Points pts;
    for (int ipoint = 0; ipoint < fdata.size(); ++ipoint) {
      ezc3d::DataNS::Points3dNS::Point pt;
      Rcpp::NumericVector pdata = Rcpp::as<Rcpp::NumericVector>(fdata[ipoint]);
      std::vector<double> pvec(pdata.begin(), pdata.end());
      float res = rdata(iframe, ipoint);
      pt.x(pvec[0]);
      pt.y(pvec[1]);
      pt.z(pvec[2]);
      pt.residual(res);
      pts.point(pt);
    }

    // set analog data
    ezc3d::DataNS::AnalogsNS::Analogs a;
    for (int i=0; i < adata.nrow(); ++i) {
      ezc3d::DataNS::AnalogsNS::SubFrame subframe;
      for (int j=0; j < adata.ncol(); ++j){
        ezc3d::DataNS::AnalogsNS::Channel c;
        c.data(adata(i,j));
        subframe.channel(c);
      }
      a.subframe(subframe);
    }

    f.add(pts, a);
    c3d.frame(f, iframe);
  }

  // write file
  c3d.write(filepath);
  return true;
}
