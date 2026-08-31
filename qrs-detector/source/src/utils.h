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

int searchPeak(
    const std::span<double>& W,
    const int& delay,
    const int& searchRadius) {

  int start = delay - searchRadius;
  int end   = delay + searchRadius;
  int bestIdx = delay;
  double bestPeak = W[delay];
  for (int i = start; i <= end; ++i) {
      if (W[i] > W[i-1] &&
          W[i] > W[i+1] &&
          W[i] > bestPeak) {
          bestPeak = W[i];
          bestIdx = i;
      }
  }
  return bestIdx;
}

double findMaxSlope(
    const std::span<double>& DW,
    const double& current_max_slope) {
  int max_slope = std::abs(DW[1] - DW[2]);
  int current_slope;
  for (int i = 2; i <= current_max_slope-1; i++) {
    current_slope = std::abs(DW[i]-DW[i+1]);
    if (current_slope > max_slope) {
      max_slope = current_slope;
    }
  }
  return max_slope;
}

double max(const std::span<double>& W) {
  return *std::max_element(W.begin(), W.end());
}
