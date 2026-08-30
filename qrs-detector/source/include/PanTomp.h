#ifndef PANTOMP
#define PANTOMP

#include "bandpass.h"

#include <deque>
#include <vector>
#include <fstream>
#include <memory>

class PanTomp {
  public:
    PanTomp(double& fs, double& T, int& T_train, int& searchRadius);
    void process(const double& x);
    void add_pretrain();
    void pretrain();
    void detect();
    void write(std::ofstream& output, const double& x);
  private:
    int searchPeak();

    int delay; // Estimated delay due to the filters
               // Which is estimated externally
    int searchRadius; // Search radius to find the candidate
                      // peak in the filtered signal

    std::deque<double> X;    // Raw inputs
    std::deque<double> Y;    // Bandpass outputs
    std::deque<double> W;    // Filtered data
    std::deque<double> DW;   // Averaged data
    std::deque<double> preW; // Pretraining window

    // Intermediates
    double y_filt;
    double y_diff;
    double y_squared;
    double y_int;
    int found;

    // Adaptive thresholds for integrated signal
    double SPKI;
    double NPKI;
    double thresI1;
    double thresI2;

    // Adaptive thresholds for filtered signal
    double SPKF;
    double NPKF;
    double thresF1;
    double thresF2;

    Bandpass bandpass;
};

#endif
