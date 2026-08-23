#include <deque>
#include <vector>

double diff(std::deque<double>& Y) {
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
