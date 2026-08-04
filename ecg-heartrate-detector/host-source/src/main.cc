#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>

#include "BandPassFilter.h"

namespace fs = std::filesystem;

int main() {

  fs::path SRC_DIR = fs::current_path();
  fs::path INPUT = SRC_DIR.parent_path() / "data" / "118e00.raw";
  fs::path OUTPUT = SRC_DIR.parent_path() / "data" / "output.csv";

  BandPassFilter filter;

  std::ifstream file(
      INPUT,
      std::ios::binary
      );
  std::ofstream outputFile(OUTPUT);

  int16_t sample;

  if (file.is_open() && outputFile) {

    while (file.read(
      reinterpret_cast<char*>(&sample),
      sizeof(sample))) 
    {
      outputFile << sample << "," << filter.process(sample) << "\n";
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
