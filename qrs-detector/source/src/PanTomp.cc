#include "PanTomp.h"
#include "bandpass.h"
#include "math.h"

#include <numeric>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

PanTomp::PanTomp(double& fs, double& T, int& T_train):
  X(5, 0.0),
  Y(5, 0.0),
  W(static_cast<std::size_t>(std::round(fs*T)), 0.0),
  DW(static_cast<std::size_t>(std::round(fs*T)), 0.0),
  preW(static_cast<std::size_t>(std::round(fs*T_train)), 0.0),
  bandpass()
{}

void PanTomp::process(const double& x) {
    X.pop_back();
    X.push_front(x);

    y_filt = bandpass.filter(X, Y);

    Y.pop_back();
    Y.push_front(y_filt);
    
    y_diff = diff(Y);
    y_squared = square(y_diff);

    W.pop_back();
    W.push_front(y_squared);

    y_int = average(W);
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
  NPKI = 0.5*average(preW);
  thresI1 = NPKI*0.25*(SPKI-NPKI);
  thresI2 = 0.5*thresI1;

  SPKF = 0.25*max(preW);
  NPKF = 0.5*average(preW);
  thresF1 = NPKF*0.25*(SPKF-NPKF);
  thresF2 = 0.5*thresF1;

  // Pretraining window is no longer needed
  preW.clear();
  preW.shrink_to_fit();
  return;
}

void PanTomp::detect() {
  if (!(DW[0] < DW[1] &&
        DW[1] > DW[2])) {
    return;
  }
  double peakI = DW[1];
  if (peakI > thresI1) {
    double peakF = searchPeak();
    if (peakF > thresF1) {
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
         << y_int << "\n";
  return;
}

int PanTomp::searchPeak(const int& idx) {
  return 0;
}
