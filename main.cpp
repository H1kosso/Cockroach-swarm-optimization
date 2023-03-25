#include <iostream>
#include <vector>
#include <algorithm>
#include <testfunctions.h>
#include "csoalgorithm.h"
#include <math.h>


int main()
{
    int numberOfCockroaches = 500;
    int maxIterations = 200;
    double eps = 0.001;
    double visual = 0.1;
    int dim = 2;
    double W = 0.1;
    double lowerBound = -500;
    double upperBound = 500;

    double (*testFunction)(std::vector<double>,int) = &Schwefel;
    CSOAlgorithm algorytm(numberOfCockroaches, dim, maxIterations, lowerBound, upperBound, visual, eps, W, testFunction);
    std::vector<double> solution = algorytm.calculateGlobalOptimum();
    std::cout << "Znaleziono rozwiazanie: " << std::endl;
    std::cout << "F(x) = " << Schwefel(solution, dim) << " dla x { ";
    for(auto x : solution) {
        std::cout << x << " ";
    }
    std::cout << "}" << std::endl;






    return 0;
}
