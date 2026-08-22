#ifndef BANDPASS
#define BANDPASS

#include <deque>
#include <vector>

class Bandpass {
  public:
    Bandpass()=default;
    std::deque<double> filter(double x);
  private:
    std::deque<double> X;
    std::deque<double> Y;

    std::vector<double> b;
    std::vector<double> a;
};
