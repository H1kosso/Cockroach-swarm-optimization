#include "testfunctions.h"

#include <math.h>

#include <iostream>
#include <vector>

const double PI = 3.14159265;

double Schwefel(std::vector<double>& x, int dim) {
    double       sum           = 0.0;
    const double schwefelConst = 418.9829;

    for (int i = 1; i <= dim; i++) {
        sum += x[i - 1] * sin(sqrt(fabs(x[i - 1])));
    }
    return schwefelConst * dim - sum;
}

double Rastring(std::vector<double>& x, int dim) {
    double sum = 0.0;
    for (int i = 1; i <= dim; i++) {
        sum += (x[i - 1] * x[i - 1]) - 10 * cos(PI * 2 * x[i - 1]);
    }
    return 10 * dim + sum;
}

double HiperElipsoide(std::vector<double>& x, int dim) {
    double sum = 0.0;
    for (int i = 1; i <= dim; i++) {
        sum += i * (x[i - 1] * x[i - 1]);
    }
    return sum;
}
