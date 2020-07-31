#include "../include/fitProcedure.h"
// #include "../include/expdata.h"
#include "../include/energyFormulas.h"

Fit::Fit()
{
    startTime = std::chrono::high_resolution_clock::now();
}

Fit::~Fit()
{
    measureTime();
}

void Fit::measureTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto endPoint = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();
    auto startPoint = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
    auto durationms = static_cast<double>((endPoint - startPoint) * 0.001);
    std::cout << "The program finished succesfully \n";
    std::cout << "Process took " << durationms << " ms..."
              << "\n";
}

double Fit::rmsCalculation(std::vector<double> &expdata, std::vector<double> &thdata)
{
    //stop if the arrays have different sizes
    if (expdata.size() != thdata.size())
        return 6969;
    double sum = 0;
    int ok = 1;
    int errorcheck = 0;
    auto size = expdata.size();
    for (int id = 0; id < size && ok; ++id)
    {
        auto currentrms = pow(expdata.at(id) - thdata.at(id), 2);
        if (isnan(currentrms))
        {
            ok = 0;
            id = 6969;
        }
        else
        {
            sum += currentrms;
            errorcheck++;
        }
    }
    auto rms = static_cast<double>(sqrt(sum / (size + 1)));
    if (!isnan(rms) && errorcheck == size)
        return rms;
    return 6969;
}

void Fit::generateTheoreticalData(ExperimentalData &obj, std::vector<double> &finalStack, double theta, double i1, double i2, double i3)
{
    auto j = EnergyFormulae::jSP;
    auto yrastSize = ExperimentalData::spin0.size() - 1;
    auto tw1Size = ExperimentalData::spin1.size();
    auto tw2Size = ExperimentalData::spin2.size();
    auto totalSize = yrastSize + tw1Size + tw2Size;
    int errorchecker = 0;
    //fill the YRAST BAND
    for (auto id = 0; id < yrastSize; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::yrast0(I, j, theta, i1, i2, i3);
        //only add valid numbers
        if (energy_I != 6969)
        {
            finalStack.emplace_back(energy_I);
            errorchecker++;
        }
        else
        {
            /* code */
        }
    }

    //fill the TW1 BAND
    for (auto id = yrastSize; id < tw1Size + yrastSize; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::tw1(I, j, theta, i1, i2, i3);
        //only add valid numbers
        if (energy_I != 6969)
        {
            finalStack.emplace_back(energy_I);
            errorchecker++;
        }
        else
        {
            /* code */
        }
    }

    //fill the TW2 BAND
    for (auto id = tw1Size + yrastSize; id < tw1Size + yrastSize + tw2Size; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::tw2(I, j, theta, i1, i2, i3);
        //only add valid numbers
        if (energy_I != 6969)
        {
            finalStack.emplace_back(energy_I);
            errorchecker++;
        }
    }
    //check if the generated array has the correct size;
    if (errorchecker != totalSize)
        std::cout << "SHOULD FAIL IN RMS CALCULATION..."
                  << "\n";
}

void Fit::getMinimum_RMS(ExperimentalData &obj, paramSet &bestParams)
{
    paramLimits limits;

    //get the experimental results from the class-object
    auto expEnergies = obj.energies;

    double minval = 9876543210.123;

    int noIterations = 0;
    //start searching for the minimum rms
    for (double i1 = limits.I_left; i1 <= limits.I_right; i1 += limits.I_step)
    {
        for (double i2 = limits.I_left; i2 <= limits.I_right; i2 += limits.I_step)
        {
            for (double i3 = limits.I_left; i3 <= limits.I_right; i3 += limits.I_step)
            {
                for (double theta = limits.theta_left; theta <= limits.theta_right; theta += limits.theta_step)

                {
                    //generate the theoretical stack
                    std::vector<double> thEnergies;

                    //populate the theoretical energies stack
                    Fit::generateTheoreticalData(obj, thEnergies, theta, i1, i2, i3);

                    //calculate the rms with the current generated excitation energies
                    auto currentRMS = rmsCalculation(expEnergies, thEnergies);

                    //store the value (if less then current minval)
                    if (currentRMS <= minval && currentRMS != 6969)
                    {
                        minval = currentRMS;
                        bestParams.I1_min = i1;
                        bestParams.I2_min = i2;
                        bestParams.I3_min = i3;
                        bestParams.theta_min = theta;
                        bestParams.RMS_min = minval;
                    }
                    //count the iterations
                    noIterations++;
                }
            }
        }
    }
    std::cout << "Searching for the best RMS finished..."
              << "\n";
    std::cout << "Total number of iterations= " << noIterations << "\n";
}

void Fit::getMinimum_RMS_fixedTheta(ExperimentalData &obj, paramSet &bestParams)
{

    paramLimits limits;

    //get the experimental results from the class-object
    auto expEnergies = obj.energies;

    double minval = 9876543210.123;
    const double theta = 109;

    int noIterations = 0;
    //start searching for the minimum rms
    for (double i1 = limits.I_left; i1 <= limits.I_right; i1 += limits.I_step)
    {
        for (double i2 = limits.I_left; i2 <= limits.I_right; i2 += limits.I_step)
        {
            for (double i3 = limits.I_left; i3 <= limits.I_right; i3 += limits.I_step)
            {
                //generate the theoretical stack
                std::vector<double> thEnergies;

                //populate the theoretical energies stack
                Fit::generateTheoreticalData(obj, thEnergies, theta, i1, i2, i3);

                //calculate the rms
                auto currentRMS = rmsCalculation(expEnergies, thEnergies);

                //store the value (if less then current minval)
                if (currentRMS <= minval && currentRMS != 6969)
                {
                    minval = currentRMS;
                    bestParams.I1_min = i1;
                    bestParams.I2_min = i2;
                    bestParams.I3_min = i3;
                    bestParams.RMS_min = minval;
                }
                //count the iterations
                noIterations++;
            }
        }
    }
    std::cout << "Searching for the best RMS finished..."
              << "\n";
    std::cout << "Total number of iterations= " << noIterations << "\n";
}