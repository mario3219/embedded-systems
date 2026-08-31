#include "math.h"

#include <deque>
#include <vector>
#include <algorithm>

double diff(const std::deque<double>& Y) {
  std::vector<double> d{
    -0.125,
    -0.25,
    0.0,
    0.25,
    0.125
  };
  double dy;
  for (int i = 0; i < 5; i++) {
    dy += d[i]*Y[i];
  }
  return dy; 
}

double square(const double& dy) {
  return dy*dy;
}

double max(const std::deque<double>& W) {
  return *std::max_element(W.begin(), W.end());
}
