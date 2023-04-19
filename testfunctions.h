#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H
#include <vector>
#include <string>

#include "exprtk.hpp"

double Schwefel(std::vector<double>& x, int dim);
double Rastring(std::vector<double>& x, int dim);
double HiperElipsoide(std::vector<double>& x, int dim);
double CustomFunction(std::vector<double>& x, int dim);
void setFunctionToParse(std::string expresion);

#endif  // TESTFUNCTIONS_H
