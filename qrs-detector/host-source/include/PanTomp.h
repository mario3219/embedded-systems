#ifndef BANDPASS
#define BANDPASS

#include <deque>
#include <vector>

class PanTomp {
  public: 
          PanTomp(double fs, double T);
          double process(double x);
  private:
          void bandpass();
          double differentiate();
          double square(double& dy);
          double window_int(double& dy_2);
          
          // processed data window
          std::deque<double> w;

          // Signals
          std::deque<double> X;
          std::deque<double> Y;

          // bandpass variables
          double b0, b1, b2, b3, b4;
          double a1, a2, a3, a4;

          // differention kernel
          double d1, d2, d3, d4, d5;
};
#endif
