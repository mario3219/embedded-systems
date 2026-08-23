#include <numeric>
#include <deque>

double window_int(std::deque<double>& w) {
  double sum = std::accumulate(std::begin(w), std::end(w), 0.0, std::plus<double>());
  return sum/w.size();
}
