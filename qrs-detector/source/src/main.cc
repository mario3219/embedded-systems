#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>

#include "bandpass.h"

double diff(std::deque<double>& data);
double square(double& data);
double window_int(std::deque<double>& data);

namespace fs = std::filesystem;

inline double mean(const std::deque<double>& init_vals) {
  return std::accumulate(
      std::begin(init_vals),
      std::end(init_vals), 
      0.0,
      std::plus<double>()
      )/init_vals.size();
}

inline double max(const std::deque<double>& W) {
  return *std::max_element(W.begin(), W.end());
}

inline double process(
    int16_t x,
    Bandpass& bandpass,
    std::deque<double>& X,
    std::deque<double>& Y,
    std::deque<double>& W,
    double& y_filt,
    double& y_diff,
    double& y_squared
) {
    X.pop_back();
    X.push_front(static_cast<double>(x));

    y_filt = bandpass.filter(X, Y);

    Y.pop_back();
    Y.push_front(y_filt);

    y_diff = diff(Y);
    y_squared = square(y_diff);

    W.pop_back();
    W.push_front(y_squared);

    return window_int(W);
}

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

  // algorithm outputs
  double y_filt;
  double y_diff;
  double y_squared;
  double y_int;

  // data containers
  std::deque<double> X(5, 0.0);
  std::deque<double> Y(5, 0.0);
  std::deque<double> W(std::round(fs*T), 0.0);
  std::deque<double> init_vals;

  // decision thresholding variables
  double thres_1;
  double thres_2;
  double spk;
  double npk;
  double maxf;
  double meanf;

  // For calculating maximum amplitude in the first 2s
  int init_timer = 0;
  int init_limit = fs*2;
  int timer = 0;
  int limit = std::round(fs*T);

  // open input stream
  std::ifstream file(INPUT, std::ios::binary);
  std::ofstream outputFile(OUTPUT);

  if (file.is_open() && outputFile) {
    while (file.read(reinterpret_cast<char*>(&x), sizeof(x))) {

    y_int = process(
        x,
        bandpass,
        X,
        Y,
        W,
        y_filt,
        y_diff,
        y_squared
    );

    if (init_timer == init_limit) {

      meanf = mean(init_vals);
      maxf = max(init_vals);

      thres_1 = maxf/3;
      thres_2 = 0.5*meanf;
      spk = thres_1;
      npk = thres_2;
      
      timer = 0;
      init_timer = 100000;

    } else {
      init_vals.push_front(y_int);
      init_timer += 1;
    }
    
    if (init_timer >= init_limit && timer >= limit) {
      spk = 0.75*max(W)+0.25*spk;
      npk = 0.75*max(W)+0.25*npk;
      thres_1 = npk+0.25*(spk-npk);
      thres_2 = 0.4*thres_1;
      timer = 0;
    } else {
      timer += 1;
    }

    outputFile << x << "," 
               << y_filt << ","
               << y_diff << ","
               << y_squared << ","
               << y_int << ","
               << thres_1 << ","
               << thres_2 << "\n";
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
