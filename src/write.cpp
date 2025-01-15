#include <Rcpp.h>
#include "ezc3d_all.h"
using namespace Rcpp;
using namespace ezc3d;

// [[Rcpp::export]]
bool write(const std::string &filepath, List object) {
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
      if (Rf_isInteger(value)) {
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

  // write point data
  Rcpp::List data = object["data"];
  for (int iframe = 0; iframe < data.size(); ++iframe) {
    Rcpp::List fdata = data[iframe];
    ezc3d::DataNS::Frame f;
    ezc3d::DataNS::Points3dNS::Points pts;

    for (int ipoint = 0; ipoint < fdata.size(); ++ipoint) {
      ezc3d::DataNS::Points3dNS::Point pt;
      Rcpp::NumericVector pdata = Rcpp::as<Rcpp::NumericVector>(fdata[ipoint]);
      std::vector<double> pvec(pdata.begin(), pdata.end());
      pt.x(pvec[0]);
      pt.y(pvec[1]);
      pt.z(pvec[2]);
      pts.point(pt);
    }
    f.add(pts);
    c3d.frame(f, iframe);
  }

  // write file
  c3d.write(filepath + ".c3d");
  return true;
}

