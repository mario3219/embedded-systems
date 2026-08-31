#ifndef BANDPASS
#define BANDPASS

#include <array>

class Bandpass {
  public:
    Bandpass()=default;
    double filter(
        const std::array<double, 5>& X, 
        const std::array<double, 5>& Y
    );
  private:
    static const std::array<double, 5> b;
    static const std::array<double, 4> a;
};
#endif
