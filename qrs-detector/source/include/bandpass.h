#ifndef BANDPASS
#define BANDPASS

#include <deque>
#include <vector>

class Bandpass {
  public:
    Bandpass();
    double filter(std::deque<double>& X, std::deque<double>& Y);
  private:
    std::vector<double> b;
    std::vector<double> a;
};
#endif
