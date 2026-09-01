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
    PanTomp(
        const double& fs,
        const double& T,
        const int& T_train,
        const int& searchRadius
    );
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
