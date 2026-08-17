#ifndef BANDPASS
#define BANDPASS

#include "data.h"

class BandPassFilter {
  public: 
          BandPassFilter();
          double process(Data& data);
  private:
          double b0, b1, b2, b3, b4;
          double a1, a2, a3, a4;
};
#endif
