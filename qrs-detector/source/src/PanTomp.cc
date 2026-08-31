#include "PanTomp.h"
#include "bandpass.h"
#include "utils.h"

#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

PanTomp::PanTomp(
    const double& fs,
    const double& T,
    const int& T_train,
    const int& searchRadius) {

  data.delay = 26;
  data.searchRadius = searchRadius;

  std::size_t window_size = static_cast<std::size_t>(std::round(fs*T)+data.delay);
  std::size_t train_window_size = static_cast<std::size_t>(std::round(fs*T)+data.delay);
  data.upper_timer = static_cast<int>(std::round(fs*0.360));
  data.lower_timer = static_cast<int>(std::round(fs*0.200));

  data.W.resize(window_size, 0.0);
  data.DW.resize(window_size, 0.0);
  data.preW.resize(train_window_size, 0.0);
}

void PanTomp::process(const double& x) {
  push_front(data.X, x);
  data.y_filt = bandpass.filter(data.X, data.Y);
  push_front(data.Y, data.y_filt);
  data.y_diff = diff(data.Y);
  data.y_squared = square(data.y_diff);
  push_front(data.W, data.y_squared);
  data.y_int = average(data.W,0);
  push_front(data.DW, data.y_int);
  return;
}

void PanTomp::add_pretrain() {
  push_front(data.preW, data.y_int);
  return;
}

void PanTomp::pretrain() {
  data.SPKI = 0.25*max(data.preW);
  data.NPKI = 0.5*average(data.preW, 0);
  data.thresI1 = data.NPKI*0.25*(data.SPKI-data.NPKI);
  data.thresI2 = 0.5*data.thresI1;

  data.SPKF = 0.25*max(data.preW);
  data.NPKF = 0.5*average(data.preW, 0);
  data.thresF1 = data.NPKF*0.25*(data.SPKF-data.NPKF);
  data.thresF2 = 0.5*data.thresF1;

  // Pretraining window is no longer needed
  data.preW.clear();
  data.preW.shrink_to_fit();
  return;
}

// Need to remake the timer logic
// < 200ms -> reject
// 200-360ms -> slope check
// > 360ms -> accept
void PanTomp::analyze() {
  data.counter++;
  data.found_beat = 0; // temp
  if (data.counter < data.lower_timer) {
    return;
  }
  if (!(data.DW[0] < data.DW[1] &&
        data.DW[1] > data.DW[2])) {
    return;
  }
  if (!checkThresholds()) {
    return;
  }
  if (data.counter < data.upper_timer) {
    if (!checkSlope()) {
      return;
    }
  }
  data.current_max_slope = findMaxSlope(
        data.DW,
        data.current_max_slope
      );
  addRR();
  data.counter = 0;
  data.found_beat = 1; // temp
  return;
}

void PanTomp::addRR() {
  push_front(data.RR1, data.counter);
  data.RR1_avg = average(data.RR1,0);
  if (0.92*data.RR2_avg < data.counter &&
      1.16*data.RR2_avg < data.counter) {
    push_front(data.RR2, data.counter);
    data.RR2_avg = average(data.RR2,0);
  }
  return;
}

bool PanTomp::checkSlope() {
  if (!(std::abs(data.DW[1]-data.DW[2]) < 0.5*data.current_max_slope)) {
    return true;
  } else {
    return false;
  }
}

bool PanTomp::checkThresholds() {
  bool found = false;
  double peakI = data.DW[1];
  if (peakI > data.thresI1) {
    double peakF = data.W[searchPeak()];
    if (peakF > data.thresF1) {
      found = true;
      data.SPKI = 0.125*peakI+0.875*data.SPKI;
      data.SPKF = 0.125*peakF+0.875*data.SPKF;
    } else {
      data.NPKF = 0.125*peakF+0.875*data.NPKF;
    }
  } else {
    data.NPKI = 0.125*peakI+0.875*data.NPKI;
  }
  data.thresI1 = data.NPKI+0.25*(data.SPKI-data.NPKI);
  data.thresI2 = 0.5*data.thresI1;

  data.thresF1 = data.NPKF+0.25*(data.SPKF-data.NPKF);
  data.thresF2 = 0.5*data.thresF1;
  return found;
}

void PanTomp::write(std::ofstream& output, const double& x) {
  data.write(output, x);
  return;
}
