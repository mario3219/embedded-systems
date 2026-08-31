#ifndef PANTOMP
#define PANTOMP

#include "bandpass.h"

#include <deque>
#include <vector>
#include <fstream>
#include <memory>
#include "utils.h"
#include "PanTompData.h"

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

    PanTompData data;
    Bandpass bandpass;
};

#endif
