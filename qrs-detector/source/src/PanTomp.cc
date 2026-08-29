#include "PanTomp.h"
#include "bandpass.h"
#include "math.h"

#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

PanTomp::PanTomp(double& fs, double& T):
  X(5, 0.0),
  Y(5, 0.0),
  W(std::round(fs*T), 0.0),
  bandpass()
{}

void PanTomp::process(const double& x) {
    X.pop_back();
    X.push_front(static_cast<double>(x));

    y_filt = bandpass.filter(X, Y);

    Y.pop_back();
    Y.push_front(y_filt);
    
    y_diff = diff(Y);
    y_squared = square(y_diff);

    W.pop_back();
    W.push_front(y_squared);

    y_int = average(W);
  return;
}

void PanTomp::pretrain(const int& timer, const int& counter) {
  return;
}

void PanTomp::detect(const int& timer, const int& counter) {
  return;
}

void PanTomp::write(std::ofstream& output, const double& x) {
  output << x << "," 
         << y_filt << ","
         << y_diff << ","
         << y_squared << ","
         << y_int << "\n";
  return;
}
