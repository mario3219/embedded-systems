#ifndef PANTOMP
#define PANTOMP

#include "bandpass.h"

#include <deque>
#include <vector>
#include <fstream>

class PanTomp {
  public:
    PanTomp(double& fs, double& T);
    void process(const double& x);
    void pretrain(const int& timer, const int& counter);
    void detect(const int& timer, const int& counter);
    void write(std::ofstream& output, const double& x);
  private:
    std::deque<double> X;
    std::deque<double> Y;
    std::deque<double> W;
    std::deque<double> init_vals;
    double y_filt;
    double y_diff;
    double y_squared;
    double y_int;

    Bandpass bandpass;

};

#endif
