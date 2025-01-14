#include <Rcpp.h>
#include "ezc3d_all.h"
using namespace Rcpp;
using namespace ezc3d;

// [[Rcpp::export]]
bool write(const std::string &filepath) {
  ezc3d::c3d c3d;
  c3d.write(filepath + ".c3d");
  return true;
}

