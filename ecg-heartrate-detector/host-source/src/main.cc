#include <iostream>
#include "BandPassFilter.h"

int main() {
  BandPassFilter filter;
  int y;
  y = filter.process(5);
  std::cout << y << "\n";
  return 0;
}
