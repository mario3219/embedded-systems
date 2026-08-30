#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>

#include "PanTomp.h"

namespace fs = std::filesystem;

int main() {

  // paths
  fs::path SRC_DIR = fs::current_path();
  fs::path INPUT = SRC_DIR.parent_path().parent_path() / "data" / "118e00.raw";
  fs::path OUTPUT = SRC_DIR.parent_path().parent_path() / "data" / "output.csv";

  // declare
  double fs = 250;
  double T = 0.150;
  int T_train = 2; // How many seconds to train for
  int searchRadius = 10; // Radius to search for candidate peak
  int timer = fs*2;   // Learning phase uses first 2s of samples
  int counter = 0;
  PanTomp pt(fs, T, T_train, searchRadius);

  // open streams
  std::ifstream file(INPUT, std::ios::binary);
  std::ofstream outputFile(OUTPUT);

  int16_t x;
  if (file.is_open() && outputFile) {
    while (file.read(reinterpret_cast<char*>(&x), sizeof(x))) {
      pt.process(static_cast<double>(x));
      pt.add_pretrain();
      pt.write(outputFile, static_cast<double>(x));
      if (counter == timer) {
        pt.pretrain();
        break;
      }
    }
    while (file.read(reinterpret_cast<char*>(&x), sizeof(x))) {
      pt.process(static_cast<double>(x));
      pt.write(outputFile, static_cast<double>(x));
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
