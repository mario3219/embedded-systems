#include "bandpass.h"

namespace {
    constexpr std::array<double, 5> b{
        0.00676541,0.0,-0.01353083,0.0,0.00676541
    };

    constexpr std::array<double, 4> a{
       -3.71130645,5.20935543,-3.27886753,0.78128048
    };
}

double Bandpass::filter(
    const std::array<double, 5>& X,
    const std::array<double, 5>& Y) {
  double y = 0.0;
  for (int i = 0; i < 5; i++) {
    y += b[i]*X[i];
  }
  for (int i = 0; i < 4; i++) {
    y -= a[i]*Y[i];
  }
  return y;
}
