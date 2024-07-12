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
NumericVector data(const std::string &filepath) {
  ezc3d::c3d f = c3d(filepath);
  float x = f.data().frame(0).points().point(0).x();
  float y = f.data().frame(0).points().point(0).y();
  float z = f.data().frame(0).points().point(0).z();
  float res = f.data().frame(0).points().point(0).residual();
  return {x,y,z,res};
}
