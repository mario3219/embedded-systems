#include <iostream>
#include <fstream>
#include "PanTompData.h"
#include "utils.h"

void PanTompData::write(
    std::ofstream& output,
    double x) const {
  output << x << "," 
         << y_filt << ","
         << y_diff << ","
         << y_squared << ","
         << y_int << ","
         << found_beat << ","
         << thresI1 << ","
         << thresF1 << "\n";
  std::cout << found_beat << "\n";
  return;
}
