#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H
#include <vector>

#include "exprtk.hpp"

double Schwefel(std::vector<double>& x, int dim);
double Rastring(std::vector<double>& x, int dim);
double HiperElipsoide(std::vector<double>& x, int dim);
double CustomFunction(std::vector<double>& x, int dim);
#endif  // TESTFUNCTIONS_H
