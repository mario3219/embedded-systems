#include "PanTomp.h"
#include "bandpass.h"
#include "math.h"

#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

PanTomp::PanTomp(double& fs, double& T, int& T_train, int& searchRadius):
  
  // Search properties due to the filter characteristics
  delay(26),
  searchRadius(searchRadius),

  // Data containers
  X(5, 0.0),
  Y(5, 0.0),
  found_beat(0),

  DW(static_cast<std::size_t>(std::round(fs*T)+delay), 0.0),
  W(static_cast<std::size_t>(std::round(fs*T)+delay), 0.0),
  RR1(8, 0),
  RR2(8, 0),

  // Pretraining window
  preW(static_cast<std::size_t>(std::round(fs*T_train)), 0.0),

  // Initial RR limits
  RR1_avg(0.0),
  RR2_avg(0.0),

  // A QRS complex can't physiologically occur within 200ms of each other
  // but can occur within 360ms, but can be misinterpreted as a T-wave
  counter(0),
  upper_timer(static_cast<int>(std::round(fs*0.360))),
  lower_timer(static_cast<int>(std::round(fs*0.200))),
  
  // The filter
  bandpass()
{}

void PanTomp::process(const double& x) {
    X.pop_back(); X.push_front(x);
    y_filt = bandpass.filter(X, Y);
    Y.pop_back();Y.push_front(y_filt);
    y_diff = diff(Y);
    y_squared = square(y_diff);
    W.pop_back(); W.push_front(y_squared);
    y_int = average(W, delay);
    DW.pop_back();
    DW.push_front(y_int);
  return;
}

void PanTomp::add_pretrain() {
  preW.pop_back();
  preW.push_front(y_int);
  return;
}

void PanTomp::pretrain() {
  SPKI = 0.25*max(preW);
  NPKI = 0.5*average(preW, 0);
  thresI1 = NPKI*0.25*(SPKI-NPKI);
  thresI2 = 0.5*thresI1;

  SPKF = 0.25*max(preW);
  NPKF = 0.5*average(preW, 0);
  thresF1 = NPKF*0.25*(SPKF-NPKF);
  thresF2 = 0.5*thresF1;

  // Pretraining window is no longer needed
  preW.clear();
  preW.shrink_to_fit();
  return;
}

// Need to remake the timer logic
// < 200ms -> reject
// 200-360ms -> slope check
// > 360ms -> accept
void PanTomp::analyze() {
  counter++;
  found_beat = 0; // temp
  if (counter < lower_timer) {
    return;
  }
  if (!(DW[0] < DW[1] &&
        DW[1] > DW[2])) {
    return;
  }
  if (!checkThresholds()) {
    return;
  }
  if (counter < upper_timer) {
    if (!checkSlope()) {
      return;
    }
  }
  current_max_slope = findMaxSlope();
  addRR();
  counter = 0;
  found_beat = 1; // temp
  return;
}

void PanTomp::addRR() {
  RR1.pop_back();
  RR1.push_front(counter);
  RR1_avg = average(RR1,0);
  if (0.92*RR2_avg < counter &&
      1.16*RR2_avg < counter) {
    RR2.pop_back();
    RR2.push_front(counter);
    RR2_avg = average(RR2,0);
  }
  return;
}

bool PanTomp::checkSlope() {
  bool found = false;
  if (!(std::abs(DW[1]-DW[2]) < 0.5*current_max_slope)) {
    found = true;
  }
  return found;
}

bool PanTomp::checkThresholds() {
  bool found = false;
  double peakI = DW[1];
  if (peakI > thresI1) {
    double peakF = W[searchPeak()];
    if (peakF > thresF1) {
      found = true;
      SPKI = 0.125*peakI+0.875*SPKI;
      SPKF = 0.125*peakF+0.875*SPKF;
    } else {
      NPKF = 0.125*peakF+0.875*NPKF;
    }
  } else {
    NPKI = 0.125*peakI+0.875*NPKI;
  }
  thresI1 = NPKI+0.25*(SPKI-NPKI);
  thresI2 = 0.5*thresI1;

  thresF1 = NPKF+0.25*(SPKF-NPKF);
  thresF2 = 0.5*thresF1;
  return found;
}

int PanTomp::searchPeak() {
    int start = delay - searchRadius;
    int end   = delay + searchRadius;
    int bestIdx = delay;
    double bestPeak = W[delay];
    for (int i = start; i <= end; ++i) {
        if (W[i] > W[i-1] &&
            W[i] > W[i+1] &&
            W[i] > bestPeak) {
            bestPeak = W[i];
            bestIdx = i;
        }
    }
    return bestIdx;
}

double PanTomp::findMaxSlope() {
  int max_slope = std::abs(DW[1] - DW[2]);
  int current_slope;
  for (int i = 2; i <= current_max_slope-1; i++) {
    current_slope = std::abs(DW[i]-DW[i+1]);
    if (current_slope > max_slope) {
      max_slope = current_slope;
    }
  }
  return max_slope;
}

void PanTomp::write(std::ofstream& output, const double& x) {
  output << x << "," 
         << y_filt << ","
         << y_diff << ","
         << y_squared << ","
         << y_int << ","
         << found_beat << ","
         << thresI1 << ","
         << thresF1 << "\n";
  return;
}
