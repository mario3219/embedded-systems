#include "PanTomp.h"
#include "bandpass.h"
#include "math.h"

#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

PanTomp::PanTomp(double& fs, double& T, int& T_train, int& searchRadius):
  X(5, 0.0),
  Y(5, 0.0),
  DW(3, 0.0),
  delay(26),
  found(0),
  searchRadius(searchRadius),
  W(static_cast<std::size_t>(std::round(fs*T)+delay), 0.0),
  preW(static_cast<std::size_t>(std::round(fs*T_train)), 0.0),
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

void PanTomp::detect() {
  found = 0; // temp
  if (!(DW[0] < DW[1] &&
        DW[1] > DW[2])) {
    return;
  }
  double peakI = DW[1];
  if (peakI > thresI1) {
    double peakF = W[searchPeak()];
    if (peakF > thresF1) {
      found = 1;  // temp
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
  return;
}

void PanTomp::write(std::ofstream& output, const double& x) {
  output << x << "," 
         << y_filt << ","
         << y_diff << ","
         << y_squared << ","
         << y_int << ","
         << found << ","
         << thresI1 << ","
         << thresF1 << "\n";
  return;
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
