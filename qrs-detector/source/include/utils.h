#ifndef MATH
#define MATH

#include <array>
#include <numeric>
#include <span>

double diff(const std::array<double, 5>& Y);
double square(const double& dy);
int searchPeak();
double findMaxSlope(
    const std::span<const double>& DW,
    const double& current_max_slope
    );
double max(const std::span<const double>& W);

//double average(
//    const std::span<const double>& w,
//    std::size_t delay);

template <typename T>
double average(std::span<const T> w, std::size_t delay)
{
    double sum = std::accumulate(
        w.begin(),
        w.end() - delay,
        0.0
    );

    return sum / static_cast<double>(w.size() - delay);
}

template <typename Container>
double average(const Container& w, std::size_t delay)
{
    return average(
        std::span{w},
        delay
    );
}

template <typename Container, typename T>
void push_front(Container& data, const T& value)
{
    for (std::size_t i = data.size() - 1; i > 0; --i) {
        data[i] = data[i - 1];
    }

    data[0] = value;
}

#endif
