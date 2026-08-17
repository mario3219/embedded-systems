#include "BandPassFilter.h"
#include "data.h"

BandPassFilter::BandPassFilter():
  
  b0(0.00676541), 
  b1(0.0), 
  b2(-0.01353083), 
  b3(0.0), 
  b4(0.00676541),
  
  a1(-3.71130645), 
  a2(5.20935543), 
  a3(-3.27886753), 
  a4(0.78128048)
  {}

double BandPassFilter::process(Data& data) {
  return 0.0;

}
