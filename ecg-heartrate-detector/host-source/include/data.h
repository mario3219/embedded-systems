#ifndef DATA
#define DATA

#include <deque>

class Data {
  public:
    Data();
    void addX(const double& x);
    void addY(const double& y);
  private:
    std::deque<double> X;
    std::deque<double> Y;
};
#endif
