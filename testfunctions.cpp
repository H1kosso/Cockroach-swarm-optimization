#include "testfunctions.h"

#include <math.h>

#include <iostream>
#include <vector>
#include "exprtk.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QDebug>
#include "testfunctions.h"


const double PI = 3.14159265;
std::string functionToParse ="";

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
