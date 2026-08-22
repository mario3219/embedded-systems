#include "bandpass.h"

Bandpass::Bandpass(): 
  b{0.00676541, 
  0.0, 
  -0.01353083, 
  0.0, 
  0.00676541},

  a{-3.71130645, 
  5.20935543, 
  -3.27886753, 
  0.78128048},

  X(5, 0.0),
  Y(5, 0.0)
{}

std::deque<double> Bandpass::filter(double x) {
  
  X.pop_back();
  X.push_front(x);

  double y;
  for (int i = 0; i < 5; i++) {
    y += b[i]*X[i];
  }
  for (int i = 0; i < 4; i++) {
    y -= a[i]*Y[i];
  }

  Y.pop_back();
  Y.push_front(y);

  return Y;
}
