#include <Rcpp.h>
#include "ezc3d.h"
using namespace Rcpp;

// [[Rcpp::export]]
int read(const std::string &filepath) {
  ezc3d::c3d c3d(filepath);
  return 5;
}
