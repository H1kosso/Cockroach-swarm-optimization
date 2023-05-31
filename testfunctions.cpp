#include "testfunctions.h"

#include <math.h>

#include <iostream>
#include <vector>
#include "exprtk.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"



const double PI = 3.14159265;
std::string functionToParse ="";
double lambda = 0;
double mi = 0;
double r = 0;
double c1 = 0;
double c2 = 0;

static inline size_t factorial(int n){
    if (n < 0){
        throw std::invalid_argument("Factorial with negative argument\n");
    }
    size_t result = 1;
    for (int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

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

void setParametertsForQue(double _lambda, double _mi, double _r, double _c1, double _c2){
    lambda = _lambda;
    mi = _mi;
    r = _r;
    c1 = _c1;
    c2 = _c2;
}

double queueFun(std::vector<double>& x, int dim){
    if (x.empty()){
        throw std::invalid_argument("Input is empty\n");
    }
    double m = x[1];
    double N = x[0];

    double p0{}, pN{};

    //setParametertsForQue(40.0, 20.0, 5.0, 1.0, 10.0);


    double rho = lambda / mi;
    size_t mFactorial = factorial(m);

    double sum = 0, roDivM = rho / m;
    if (roDivM == 1) {
        for (int k = 0; k <= m - 1; k++) {
            sum += pow(rho, k) / factorial(k);
        }
        p0 = 1 / (sum + (pow(rho, m) / mFactorial) * (N + 1.0));
    }
    else {
        for (int k = 0; k <= m - 1; k++) {
            sum += pow(rho, k) / factorial(k);
        }
        p0 = 1 / (sum + (pow(rho, m) / mFactorial) * ((1.0 - (pow(roDivM, N + 1.0))) / (1.0 - roDivM)));
    }

    // Same as pOdmowy
    pN = (pow(rho, m + N) / pow(m, N)) * (p0 / mFactorial);

    double result = -(lambda * (1 - pN) * r - c1 * N - c2 * m);
    if (isnan(result)){
        throw std::domain_error("Result is NaN. Consider domain of the problem\n");
    }
    return result;
}



void setFunctionToParse(std::string expresion){
    functionToParse = expresion;
}

template <typename T>
T functionParser(T x, T y) {

    const std::string expression_string = functionToParse ;

    exprtk::expression<T> expression;
    exprtk::parser<T> parser;
    parser.compile(expression_string, expression);

    exprtk::symbol_table<T> symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_variable("y", y);
    symbol_table.add_constants();

    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string, expression);


    double result = expression.value();
    return result;
}

double CustomFunction(std::vector<double>& x, int dim) {
    return functionParser<double>(x[0],x[1]);
}
