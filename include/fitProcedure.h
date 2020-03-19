#ifndef FITPROCEDURE_HH
#define FITPROCEDURE_HH

#include <cmath>
#include <vector>
#include <iostream>
#include "../include/expdata.h"
// #include "../include/energyFormulas.h"
class Fit
{
public:
    static double rmsCalculation(std::vector<double> &expdata, std::vector<double> &thdata);
    static void generateTheoreticalData(ExperimentalData &obj, std::vector<double> &finalStack, double theta, double i1, double i2, double i3);
};

#endif // FITPROCEDURE_HH
