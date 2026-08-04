#ifndef BANDPASS
#define BANDPASS

class BandPassFilter {
  public: 
          BandPassFilter();
          double process(double x);
  private:
          double b0, b1, b2, b3, b4;
          double a1, a2, a3, a4;
          double x1, x2, x3, x4;
          double y1, y2, y3, y4;
};
#endif
