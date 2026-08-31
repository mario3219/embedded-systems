#ifndef MATH
#define MATH

#include <deque>
#include <numeric>

double diff(const std::deque<double>& Y);
double square(const double& dy);
double max(const std::deque<double>& W);

template <typename T>
double average(const std::deque<T>& w, std::size_t delay) {
    double sum = std::accumulate(
        w.begin(),
        w.end() - delay,
        0.0
    );

    return sum / static_cast<double>(w.size() - delay);
}

#endif
