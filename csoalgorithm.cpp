#include "csoalgorithm.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QVBoxLayout>
#include <iostream>
#include <random>
#include <vector>

#include "testfunctions.h"

CSOAlgorithm::CSOAlgorithm(int numberOfCockroaches, int dim, int maxIterations, double lowerBound,
                           double upperBound, double visual, double eps, double w,
                           double (*testFunction)(std::vector<double>&, int))
    : random(rd()), bounds{lowerBound, upperBound} {
    this->numberOfCockroaches = numberOfCockroaches;
    this->dim                 = dim;
    this->maxIterations       = maxIterations;
    this->lowerBound          = lowerBound;
    this->upperBound          = upperBound;
    this->visual              = visual;
    this->eps                 = eps;
    this->w                   = w;
    this->testFunction        = testFunction;
}

std::vector<double> CSOAlgorithm::generateRandomSolution() {
    std::vector<double> solution;
    solution.reserve(dim);

    for (int i = 0; i < dim; i++) solution.push_back(bounds(random));

    return solution;
}

std::vector<double> CSOAlgorithm::findGlobalOptimum(std::vector<std::vector<double>>& cockroaches) {
    std::vector<double> globalOptimum;
    int                 dim = cockroaches[0].size();

    globalOptimum = cockroaches[0];

    for (long long unsigned int i = 1; i < cockroaches.size(); i++) {
        if (testFunction(cockroaches[i], dim) < testFunction(globalOptimum, dim))
            globalOptimum = cockroaches[i];
    }

    return globalOptimum;
}

std::vector<double> CSOAlgorithm::updatePosition(std::vector<double>& position,
                                                 std::vector<double>& optimumPosition,
                                                 double               stepSize) {
    std::uniform_real_distribution<> dis{0, 1};
    std::vector<double>              newPosition(position.size());
    double                           rand, delta;

    for (long long unsigned int i = 0; i < position.size(); i++) {
        rand           = dis(random);
        delta          = rand * (optimumPosition[i] - position[i]);
        newPosition[i] = position[i] + stepSize * delta;
    }
    return newPosition;
}

double CSOAlgorithm::diffCockroaches(std::vector<double>& cockroaches_I,
                                     std::vector<double>& cockroaches_II) {
    double sum = 0;

    for (long long unsigned int i = 0; i < cockroaches_I.size(); i++) {
        sum +=
            fabs(cockroaches_I[i] - cockroaches_II[i]) * fabs(cockroaches_I[i] - cockroaches_II[i]);
    }

    return sqrt(sum);
}

bool CSOAlgorithm::isLocalOptimum(std::vector<double>& localOpt, std::vector<double>& pos) {
    for (long long unsigned int i = 0; i < localOpt.size(); i++) {
        if (localOpt[i] != pos[i])
            return false;
    }

    return true;
}

std::vector<double> CSOAlgorithm::updatePostionInLight(std::vector<double>& position) {
    std::uniform_real_distribution<> dis(0, 1);
    std::vector<double>              newPosition;
    newPosition.reserve(position.size());

    for (long long unsigned int i = 0; i < position.size(); i++) {
        newPosition.push_back(position[i] + dis(random));
    }

    return newPosition;
}

std::vector<double> CSOAlgorithm::calculateGlobalOptimum(std::vector<double>& allOptimums) {
    std::vector<double>              globalOptimum;
    std::vector<double>              localOptimum;
    std::vector<std::vector<double>> cockroaches;
    std::uniform_real_distribution<> dis(1, (double)numberOfCockroaches);
    std::uniform_int_distribution<>  light(1, maxIterations);
    int                              lightIteration;
    cockroaches.reserve(numberOfCockroaches);

    for (int i = 0; i < numberOfCockroaches; i++) {
        cockroaches.push_back(generateRandomSolution());
    }

    try{
        globalOptimum = findGlobalOptimum(cockroaches);

        for (int t = 0; t < maxIterations; t++) {
            if (std::fabs(testFunction(globalOptimum, dim)) <= eps) {
                return globalOptimum;
            }

            lightIteration = light(random);

            for (int i = 0; i < numberOfCockroaches; i++) {
                for (int j = 0; j < numberOfCockroaches; j++) {
                    if (diffCockroaches(cockroaches[i], cockroaches[j]) < visual &&
                        (testFunction(cockroaches[j], dim) < testFunction(cockroaches[i], dim))) {
                        localOptimum = cockroaches[j];
                    }
                }

                if (isLocalOptimum(localOptimum, cockroaches[i])) {
                    cockroaches[i] = updatePosition(cockroaches[i], globalOptimum, w);
                } else {
                    cockroaches[i] = updatePosition(cockroaches[i], localOptimum, w);
                }

                if (testFunction(cockroaches[i], dim) < testFunction(globalOptimum, dim)) {
                    globalOptimum = cockroaches[i];
                }
            }

            if (t == lightIteration) {
                for (int i = 0; i < numberOfCockroaches; i++) {
                    cockroaches[i] = updatePostionInLight(cockroaches[i]);

                    if (testFunction(cockroaches[i], dim) < testFunction(globalOptimum, dim)) {
                        globalOptimum = cockroaches[i];
                    }
                }
            }

            int k = dis(random);

            if (!isLocalOptimum(globalOptimum, cockroaches[k])) {
                cockroaches[k] = globalOptimum;
            }
            allOptimums.push_back(testFunction(globalOptimum, dim));
        }


    }
    catch (const std::invalid_argument& ex){
        std::cerr << "Exception: " << ex.what() << '\n';
        std::exit(-1);
    }
    return globalOptimum;
}
