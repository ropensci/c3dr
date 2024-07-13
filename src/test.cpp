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

  // get point labels
  std::vector<std::string> label(f.parameters().group("POINT").parameter("LABELS").valuesAsString());

  // get data
  List d(nframes);
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
    d[i] = frame;
  }

  // get analogs
  List a(nframes);
  NumericMatrix aframe(nperframe, nanalogs); // subframes x analogchanels
  // iterate through data
  for (int i = 0; i < nframes; ++i) {
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
    Named("data") = d,
    Named("residuals") = res,
    Named("analog") = a
  );
  return(out);
}
