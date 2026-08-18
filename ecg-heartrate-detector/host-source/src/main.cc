#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <deque>
#include <cmath>

#include "PanTomp.h"

namespace fs = std::filesystem;

int main() {

  // paths
  fs::path SRC_DIR = fs::current_path();
  fs::path INPUT = SRC_DIR.parent_path() / "data" / "118e00.raw";
  fs::path OUTPUT = SRC_DIR.parent_path() / "data" / "output.csv";

  // declare variables
  double fs = 250.0;
  double T = 0.15;
  PanTomp filter(T, fs);
  double x;
  double y;

  // open input stream
  std::ifstream file(INPUT, std::ios::binary);
  std::ofstream outputFile(OUTPUT);

  if (file.is_open() && outputFile) {
    while (file.read(reinterpret_cast<char*>(&x), sizeof(x))) {
      y = filter.process(x);
      outputFile << x << "," << y << "\n";
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
