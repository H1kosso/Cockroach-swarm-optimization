#ifndef CSOALGORITHM_H
#define CSOALGORITHM_H
#include <iostream>
#include <random>
#include <vector>

#include "testfunctions.h"

class CSOAlgorithm {
private:
    int    numberOfCockroaches;
    int    dim;
    int    maxIterations;
    double lowerBound;
    double upperBound;
    double visual;
    double eps;
    double w;
    std::random_device rd; // uniform int distribution.
    std::mt19937 random; // pseudo random value, very fast
    std::uniform_real_distribution<> bounds;

    double (*testFunction)(std::vector<double>&, int);

    std::vector<double> generateRandomSolution();
    std::vector<double> findGlobalOptimum(std::vector<std::vector<double>>& cockroaches);
    std::vector<double> updatePosition(std::vector<double>& position,
                                       std::vector<double>& optimumPosition, double stepSize);
    double diffCockroaches(std::vector<double>& cockroaches_I, std::vector<double>& cockroaches_II);
    bool   isLocalOptimum(std::vector<double>& localOpt, std::vector<double>& pos);
    std::vector<double> updatePostionInLight(std::vector<double>& position);

public:
    CSOAlgorithm(int numberOfCockroaches, int dim, int maxIterations, double lowerBound,
                 double upperBound, double visual, double eśps, double w,
                 double (*testFunction)(std::vector<double>&, int));

    std::vector<double> calculateGlobalOptimum();
};

#endif  // CSOALGORITHM_H
