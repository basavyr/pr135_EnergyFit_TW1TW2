#ifndef FITPROCEDURE_HH
#define FITPROCEDURE_HH

#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include <string>
#include <chrono>
#include <ctime>

#include "../include/expdata.h"
// #include "../include/energyFormulas.h"
class Fit
{
    //include time measurement
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

public:
    Fit();
    ~Fit();
    void measureTime();

public:
    struct paramSet
    {
        double I1_min;
        double I2_min;
        double I3_min;
        double theta_min;
        double RMS_min;
        paramSet()
        {
            I1_min = 6969;
            I2_min = 6969;
            I3_min = 6969;
            theta_min = 6969;
            RMS_min = 6969;
        }
    };
    struct paramLimits
    {
        const double I_left = 1.0;
        const double I_right = 130.0;
        const double theta_left = -180.0;
        const double theta_right = 180.0;
        const double I_step = 10.0;
        const double theta_step = 10.0;
    };

public:
    static double rmsCalculation(std::vector<double> &expdata, std::vector<double> &thdata);
    static void generateTheoreticalData(ExperimentalData &obj, std::vector<double> &finalStack, double theta, double i1, double i2, double i3);
    static void getMinimum_RMS(ExperimentalData &obj, paramSet &bestParams);
    static void getMinimum_RMS_fixedTheta(ExperimentalData &obj, paramSet &bestParams);
};

#endif // FITPROCEDURE_HH
