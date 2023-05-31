#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H
#include <vector>
#include <string>

#include "exprtk.hpp"

double Schwefel(std::vector<double>& x, int dim);
double Rastring(std::vector<double>& x, int dim);
double HiperElipsoide(std::vector<double>& x, int dim);
/**
 * Evaluation of objective function in queue system M/M/m/FIFO/m+N.
 * @throws std::invalid_argument when input is empty
 * @throws std::domain_error if somehow result is NaN
*/
double queueFun(std::vector<double>& x, int dim = 2);
double CustomFunction(std::vector<double>& x, int dim);
void setFunctionToParse(std::string expresion);

#endif  // TESTFUNCTIONS_H
