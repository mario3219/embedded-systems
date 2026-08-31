#include <iostream>
#include <fstream>
#include "PanTompData.h"
#include "utils.h"

//void PanTompData::addX(const double& x) {
//  X.pop_back();
//  X.push_front(x);
//  return;
//}
//void PanTompData::addY(const double& y) {
//  Y.pop_back();
//  Y.push_front(y);
//  return;
//}
//void PanTompData::addW(const double& y_squared) {
//  W.pop_back();
//  W.push_front(y_squared);
//  return;
//}
//void PanTompData::addDW(const double& y_int) {
//  DW.pop_back();
//  DW.push_front(y_int);
//  return;
//}
//void PanTompData::addpreW() {
//  preW.pop_back();
//  preW.push_front(y_int);
//  return;
//}
//void PanTompData::addRR1() {
//  RR1.pop_back();
//  RR1.push_front(counter);
//  return;
//}
//void PanTompData::addRR2() {
//  RR2.pop_back();
//  RR2.push_front(counter);
//  return;
//}

void PanTompData::write(
    std::ofstream& output,
    double x) const {
  output << x << "," 
         << y_filt << ","
         << y_diff << ","
         << y_squared << ","
         << y_int << ","
         << found_beat << ","
         << thresI1 << ","
         << thresF1 << "\n";
  return;
}
