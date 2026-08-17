#include "data.h"
#include <deque>

Data::Data() {
  X = {0.0, 0.0, 0.0, 0.0};
  Y = {0.0, 0.0, 0.0, 0.0};
  }

  void Data::addX(const double& x) {
    X.pop_front();
    X.push_back(x);
  }

  void Data::addY(const double& y) {
    Y.pop_front();
    Y.push_back(y);
  }
