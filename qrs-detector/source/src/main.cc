#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <deque>
#include <cmath>

#include "bandpass.h"

/*
#include "diff.cc"
#include "square.cc"
#include "window_int.cc"
*/

double diff(std::deque<double>& data);
double square(double& data);
double window_int(std::deque<double>& data);

namespace fs = std::filesystem;

int main() {

  // paths
  fs::path SRC_DIR = fs::current_path();
  fs::path INPUT = SRC_DIR.parent_path().parent_path() / "data" / "118e00.raw";
  fs::path OUTPUT = SRC_DIR.parent_path().parent_path() / "data" / "output.csv";

  // declare
  Bandpass bandpass;
  double fs = 250;
  double T = 0.150;

  int16_t x;

  double y_filt;
  double y_diff;
  double y_squared;
  double y_int;

  std::deque<double> X(5, 0.0);
  std::deque<double> Y(5, 0.0);
  std::deque<double> W(std::round(fs*T), 0.0);

  // open input stream
  std::ifstream file(INPUT, std::ios::binary);
  std::ofstream outputFile(OUTPUT);

  if (file.is_open() && outputFile) {
    while (file.read(reinterpret_cast<char*>(&x), sizeof(x))) {
      
      X.pop_back(); X.push_front(static_cast<double>(x));
      y_filt = bandpass.filter(X,Y);
      Y.pop_back(); Y.push_front(y_filt);

      y_diff = diff(Y);
      y_squared = square(y_diff);

      W.pop_back(); W.push_front(y_squared);
      y_int = window_int(W);
      
      outputFile << x << "," 
                 << y_filt << ","
                 << y_diff << ","
                 << y_squared << ","
                 << y_int << "\n";
    }

  file.close();

  } else {
    std::cerr 
      << "Could not process, check paths." << "\n"
      << INPUT << "\n"
      << OUTPUT << "\n";
  }

  std::cout << "Done" << "\n";

  return 0;
}
