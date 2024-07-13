#include <Rcpp.h>
#include "ezc3d.h"
#include "Header.h"
#include "Data.h"
#include "Parameters.h"
using namespace Rcpp;
using namespace ezc3d;

// [[Rcpp::export]]
List get_header(const std::string &filepath) {
  ezc3d::c3d x = c3d(filepath);
  List out = List::create(
    Named("nframes") = x.header().nbFrames(),
    Named("npoints") = x.header().nb3dPoints(),
    Named("nanalogs") = x.header().nbAnalogs(),
    Named("analogperframe") = x.header().nbAnalogByFrame(),
    Named("framerate") = x.header().frameRate(),
    Named("nevents") = x.header().nbEvents()
  );
  return out;
}

// [[Rcpp::export]]
std::vector<std::string> get_pointnames(const std::string &filepath) {
  ezc3d::c3d x = c3d(filepath);
  std::vector<std::string> label(x.parameters().group("POINT").parameter("LABELS").valuesAsString());
  return(label);
}

// [[Rcpp::export]]
List get_data(const std::string &filepath) {
  // read data
  ezc3d::c3d f = c3d(filepath);
  // get params
  int nframes = f.header().nbFrames();
  int npoints = f.header().nb3dPoints();
  // create empty placeholders
  List out(nframes);
  List frame(npoints);
  NumericMatrix res(nframes, npoints);
  // iterate through data
  for (int i = 0; i < nframes; ++i) {
    for (int j = 0; j < npoints; ++j) {
      float x = f.data().frame(i).points().point(j).x();
      float y = f.data().frame(i).points().point(j).y();
      float z = f.data().frame(i).points().point(j).z();
      float r = f.data().frame(i).points().point(j).residual();
      NumericVector v = {x,y,z};
      frame[j] = v;
      res(i,j) = r;
    }
    out[i] = frame;
  }
  out.attr("residuals") = res;
  return(out);
}

// [[Rcpp::export]]
List get_analogs(const std::string &filepath) {
  // read data
  ezc3d::c3d f = c3d(filepath);
  // get params
  int nframes = f.header().nbFrames();
  int nperframe = f.header().nbAnalogByFrame();
  int nanalogs = f.header().nbAnalogs();
  // create empty placeholder
  List out(nframes);
  NumericMatrix frame(nperframe, nanalogs); // subframes x analogchanels
  // interate through data
  for (int i = 0; i < nframes; ++i) {
    for (int j = 0; j < nperframe; ++j) {
      for (int k = 0; k < nanalogs; ++k) {
        float a = f.data().frame(i).analogs().subframe(j).channel(k).data();
        frame(j,k) = a;
      }
    }
    out[i] = frame;
  }
  return(out);
}
