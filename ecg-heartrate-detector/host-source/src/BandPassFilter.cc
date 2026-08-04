#include "BandPassFilter.h"

BandPassFilter::BandPassFilter():
  b0(0.00676541), b1(0.0), b2(-0.01353083), b3(0.0), b4(0.00676541),
  a1(-3.71130645), a2(5.20935543), a3(-3.27886753), a4(0.78128048),
  x1(0.0), x2(0.0), x3(0.0), x4(0.0),
  y1(0.0), y2(0.0), y3(0.0), y4(0.0) {}

double BandPassFilter::process(double x) {
 
  double y = 
             b0*x
           + b1*x1
           + b2*x2
           + b3*x3
           + b4*x4
           - a1*y1
           - a2*y2
           - a3*y3
           - a4*y4;
  x4 = x3;
  x3 = x2;
  x2 = x1;
  x1 = x;

  y4 = y3;
  y3 = y2;
  y2 = y1;
  y1 = y;

  return y;

}
