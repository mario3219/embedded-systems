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
    void analyze();
    void write(std::ofstream& output, const double& x);
  private:
    void addRR();
    bool checkSlope();
    bool checkThresholds();
    int searchPeak();
    double findMaxSlope();

    std::size_t delay; // Estimated delay due to the filters
               // Which is estimated externally
    int searchRadius; // Search radius to find the candidate
                      // peak in the filtered signal
    int upper_timer;
    int lower_timer;

    std::deque<double> X;    // Raw inputs
    std::deque<double> Y;    // Bandpass outputs
    std::deque<double> W;    // Filtered data
    std::deque<double> DW;   // Averaged data
    std::deque<double> preW; // Pretraining window
    std::deque<int> RR1;     // RR intervals
    std::deque<int> RR2;

    // Intermediates
    double y_filt;
    double y_diff;
    double y_squared;
    double y_int;
    double current_max_slope;
    int found_beat; // temp

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

    // RR thresholds
    double RR1_avg;
    double RR2_avg;

    // Counter used to check if candidate peak is a T-wave
    int counter;
    int timer;

    Bandpass bandpass;
};

#endif
