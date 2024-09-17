#include <Rcpp.h>
#include "ezc3d.h"
#include "Header.h"
#include "Data.h"
#include "Parameters.h"
using namespace Rcpp;
using namespace ezc3d;

// [[Rcpp::export]]
List read(const std::string &filepath) {
  ezc3d::c3d f = c3d(filepath);

  // get header params
  int nframes = f.header().nbFrames();
  int nperframe = f.header().nbAnalogByFrame();
  int nanalogs = f.header().nbAnalogs();
  int npoints = f.header().nb3dPoints();

  // get header
  List h = List::create(
    Named("nframes") = nframes,
    Named("npoints") = npoints,
    Named("nanalogs") = nanalogs,
    Named("analogperframe") = nperframe,
    Named("framerate") = f.header().frameRate(),
    Named("nevents") = f.header().nbEvents()
  );

  // get parameters (organized in parameter groups)
  int ngroups = f.parameters().nbGroups(); // number of groups
  CharacterVector g(ngroups); // group names
  NumericVector np(ngroups); // number of parameters per group
  List p(ngroups);
  // create a list of all groups with a list of all group parameters inside
  // iterate over each group
  for (int i = 0; i < ngroups; ++i) {
    g[i] = f.parameters().group(i).name(); // group name
    np[i] = f.parameters().group(i).nbParameters(); // number of parameters
    List q(np[i]);
    CharacterVector nq(np[i]); // parameter names
    // iterate over each parameter inside a group
    for (int j = 0; j < np[i]; j++) {
      nq[j] = f.parameters().group(i).parameter(j).name();
      // convert parameter value based on data type
      ezc3d::DATA_TYPE dt(f.parameters().group(i).parameter(j).type());
      if (dt == DATA_TYPE::INT) {
        q[j] = f.parameters().group(i).parameter(j).valuesAsInt();
      } else if (dt == DATA_TYPE::FLOAT) {
        q[j] = f.parameters().group(i).parameter(j).valuesAsDouble();
      } else if (dt == DATA_TYPE::BYTE) {
        q[j] = f.parameters().group(i).parameter(j).valuesAsByte();
      } else if (dt == DATA_TYPE::WORD || dt == DATA_TYPE::CHAR){
        q[j] = f.parameters().group(i).parameter(j).valuesAsString();
      } else { // for example no or unknown data type
        q[j] = NA_LOGICAL;
      }
    };
    q.names() = nq; // write parameter names as list attribute
    p[i] = q;
  }
  p.names() = g; // write group names as list attribute

  // get point labels
  std::vector<std::string> label(f.parameters().group("POINT").parameter("LABELS").valuesAsString());

  // get analog labels
  std::vector<std::string> alabel(f.parameters().group("ANALOG").parameter("LABELS").valuesAsString());

  // get data
  List d(nframes);
  NumericMatrix res(nframes, npoints);
  // iterate through data
  for (int i = 0; i < nframes; ++i) {
    List frame(npoints);
    for (int j = 0; j < npoints; ++j) {
      float x = f.data().frame(i).points().point(j).x();
      float y = f.data().frame(i).points().point(j).y();
      float z = f.data().frame(i).points().point(j).z();
      float r = f.data().frame(i).points().point(j).residual();
      NumericVector v = {x,y,z};
      frame[j] = v;
      res(i,j) = r;
    }
    d[i] = frame;
  }

  // get analog data
  List a(nframes);
  // iterate through data
  for (int i = 0; i < nframes; ++i) {
    NumericMatrix aframe(nperframe, nanalogs); // subframes x analogchanels
    for (int j = 0; j < nperframe; ++j) {
      for (int k = 0; k < nanalogs; ++k) {
        float a = f.data().frame(i).analogs().subframe(j).channel(k).data();
        aframe(j,k) = a;
      }
    }
    a[i] = aframe;
  }

  List out = List::create(
    Named("header") = h,
    Named("labels") = label,
    Named("alabels") = alabel,
    Named("data") = d,
    Named("residuals") = res,
    Named("analog") = a,
    Named("parameters") = p
  );
  return(out);
}
