#include <Rcpp.h>
#include "ezc3d.h"
#include "Header.h"
#include "Data.h"
using namespace Rcpp;
using namespace ezc3d;

// [[Rcpp::export]]
int read(const std::string &filepath) {
  ezc3d::c3d x = c3d(filepath);
  return x.header().nbFrames();
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
  // interate through data
  for (int i = 0; i < nframes; ++i) {
    for (int j = 0; j < npoints; ++j) {
      float x = f.data().frame(i).points().point(j).x();
      float y = f.data().frame(i).points().point(j).y();
      float z = f.data().frame(i).points().point(j).z();
      float res = f.data().frame(i).points().point(j).residual();
      NumericVector v = {x,y,z,res};
      frame[j] = v;
    }
    out[i] = frame;
  }
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
