#ifndef PANTOMP_DATA
#define PANTOMP_DATA

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

class PanTompData {
  public:
    PanTompData()=default;
//    void addX(const double& x);
//    void addY(const double& y);
//    void addW(const double& y_squared);
//    void addDW(const double& y_int);
//    void addpreW();
//    void addRR1();
//    void addRR2();
    void write(std::ofstream& output, double x) const;

    std::size_t delay;  // Estimated delay due to the filters
                              // which is estimated externally
    
    int searchRadius;   // Search radius to find the candidate
                              // peak in the filtered signal
    
    int upper_timer;    // Timers to track refractory period
    int lower_timer;
    int counter = 0;

    std::array<double, 5> X{};    // Raw inputs
    std::array<double, 5> Y{};    // Bandpass outputs
    std::array<int, 8> RR1{};        // RR intervals
    std::array<int, 8> RR2{};
    std::vector<double> W;               // Filtered data
    std::vector<double> DW;              // Averaged data
    std::vector<double> preW;            // Pretraining window

    // Intermediates
    double y_filt;
    double y_diff;
    double y_squared;
    double y_int;
    double current_max_slope;
    int found_beat = 0; // temp

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
    double RR1_avg = 0.0;
    double RR2_avg = 0.0;
};

#endif
