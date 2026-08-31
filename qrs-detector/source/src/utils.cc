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

    if (W.size() < 3) {
        return -1;
    }
    int start = std::max(1, delay - searchRadius);
    int end = std::min(
        static_cast<int>(W.size()) - 2,
        delay + searchRadius
    );
    if (start > end) {
        return -1;
    }
    int bestIdx = start;
    double bestPeak = W[start];
    for (int i = start; i <= end; ++i) {
        if (W[i] > W[i - 1] &&
            W[i] > W[i + 1] &&
            W[i] > bestPeak) {

            bestPeak = W[i];
            bestIdx = i;
        }
    }
    return bestIdx;
}

double findMaxSlope(const std::span<const double>& DW) {
    if (DW.size() < 2) {
        return 0.0;
    }
    double best_slope = std::abs(DW[0] - DW[1]);
    for (std::size_t i = 1; i + 1 < DW.size(); ++i) {
        double current_slope =
            std::abs(DW[i] - DW[i + 1]);
        if (current_slope > best_slope) {
            best_slope = current_slope;
        }
    }
    return best_slope;
}

double max(const std::span<const double>& W) {
  return *std::max_element(W.begin(), W.end());
}
