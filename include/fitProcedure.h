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
    // include time measurement
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
        const double I_left = 5.0;
        const double I_right = 100.0;
        const double theta_left = -180.0;
        const double theta_right = 180.0;
        const double I_step = 1.0;
        const double theta_step = 1.0;
    };

public:
    static double rmsCalculation(std::vector<double> &expdata, std::vector<double> &thdata);
    static void generateTheoreticalData(ExperimentalData &obj, std::vector<double> &finalStack, double theta, double i1, double i2, double i3);
    static void getMinimum_RMS(ExperimentalData &obj, paramSet &bestParams);
    static void getMinimum_RMS_fixedTheta(ExperimentalData &obj, paramSet &bestParams);

    // the inertial function defined in the calculus of the triaxial potential
    static double AFunction(double spin, double I1, double I2, double oddSpin, double theta);
    // a special function which depends on the 1-2-3axes moments of inertia
    static double uFunction(double spin, double I1, double I2, double I3, double oddSpin, double theta);
    // a special function which depends on the 1-2-3axes moments of inertia
    static double kFunction(double spin, double I1, double I2, double I3, double oddSpin, double theta);
    static double ValidConditions(double spin, double I1, double I2, double I3, double oddSpin, double theta);
    static double ValidConditions_Direct(double A, double u);
    static double Validity_FullSpinRange(double I1, double I2, double I3, double oddSpin, double theta);
};

#endif // FITPROCEDURE_HH
