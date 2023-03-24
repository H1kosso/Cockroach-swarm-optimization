#include <iostream>
#include <vector>
#include <algorithm>
#include <testfunctions.h>
#include "csoalgorithm.h"
#include <math.h>

double mSchwefel(std::vector <double> x, int dim){
    double sum = 0.0;
    const double schwefelConst = 418.9829;

    for(int i = 1 ; i <= dim ; i++){
        sum += x[i-1] * sin( sqrt( fabs(x[i-1]) ) );
    }
    return schwefelConst * dim - sum;
}
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

    //To działa
    double (*testFunction)(std::vector<double>,int) = &mSchwefel;

    CSOAlgorithm algorytm(numberOfCockroaches, dim, maxIterations, lowerBound, upperBound, visual, eps, W, testFunction);
    std::vector<double> solution = algorytm.calculateGlobalOptimum();
    std::cout << "Znaleziono rozwiazanie: " << std::endl;
    std::cout << "F(x) = " << mSchwefel(solution, dim) << " dla x { ";
    for(auto x : solution) {
        std::cout << x << " ";
    }
    std::cout << "}" << std::endl;

    //Nie wiem jak dać wskaźnik do funkcji z innej klasy
    //    TestFunctions funkcje;
    //    double (*testFunctionImported)(std::vector<double>,int) = &funkcje.Schwefel;
    //    CSOAlgorithm algorytm2(numberOfCockroaches, dim, maxIterations, lowerBound, upperBound, visual, eps, W, testFunction);


    return 0;
}
