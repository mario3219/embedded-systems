#include "PanTomp.h"

#include <numeric>
#include <cmath>

// public

PanTomp::PanTomp(double fs, double T):
  b0(0.00676541), 
  b1(0.0), 
  b2(-0.01353083), 
  b3(0.0), 
  b4(0.00676541),
  
  a1(-3.71130645), 
  a2(5.20935543), 
  a3(-3.27886753), 
  a4(0.78128048),

  d1(-0.125),
  d2(-0.25),
  d3(0.0),
  d4(0.25),
  d5(0.125)

  {
    w.resize(static_cast<int>(std::round(fs*T)), 0.0); 

    // same size as the amount of filter coefficients b and a
    X.resize(5, 0.0);
    Y.resize(5, 0.0);
  }

double PanTomp::process(double x) {
  // add the new sample
  X.pop_back();
  X.push_front(x);

  bandpass();
  double dy = differentiate();
  double dy_2 = square(dy);
  return window_int(dy_2);
}

// private

void PanTomp::bandpass() {   
  double y = b0*X[0]+b1*X[1]+b2*X[2]+b3*X[3]+b4*X[4]-a1*Y[0]-a2*Y[1]-a3*Y[2]-a4*Y[3];
  Y.pop_back();
  Y.push_front(y);
}

double PanTomp::differentiate() {
  return d1*Y[4]
       + d2*Y[3]
       + d3*Y[2]
       + d4*Y[1]
       + d5*Y[0];
}

double PanTomp::square(double& dy) {
  return dy*dy;
}

double PanTomp::window_int(double& dy_2) {
  w.pop_back();
  w.push_front(dy_2);
  double sum = std::accumulate(std::begin(w), std::end(w), 0.0, std::plus<double>());
  return sum/w.size();
}
