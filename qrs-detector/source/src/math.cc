#include "math.h"

#include <algorithm>
#include <span>

double diff(const std::array<double, 5>& Y) {
    static constexpr std::array<double, 5> d{
        -0.125,
        -0.25,
         0.0,
         0.25,
         0.125
    };
    double dy = 0.0;
    for (int i = 0; i < 5; ++i) {
        dy += d[i] * Y[i];
    }
    return dy;
}

double square(const double& dy) {
  return dy*dy;
}

double max(const std::span<double>& W) {
  return *std::max_element(W.begin(), W.end());
}
