#include <iostream>

#include "../include/expdata.h"
#include "../include/energyFormulas.h"
#include "../include/fitProcedure.h"
#include <initializer_list>
#include <utility>

void newLine()
{
    std::cout << "\n";
}

void testApp()
{
    int OK = 0;
    if (!OK)
        OK = 1;
    std::cout << "App works with status " << OK << " !!!";
    newLine();
}

template <typename T>
void printArray(std::vector<T> &stack)
{
    std::cout << "{ ";
    for (auto id = 0; id < stack.size(); ++id)
    {
        if (id == stack.size() - 1)
        {
            std::cout << stack.at(id) << " };";
            newLine();
        }
        else
        {
            std::cout << stack.at(id) << " , ";
        }
    }
}

template <typename T>
void printArray_selector(std::vector<T> &stack, int left, int right)
{
    if (left >= 0 && left < stack.size() - 1 && right > 0 && right <= stack.size())
    {
        std::cout << "{ ";
        for (auto id = left; id < right; ++id)
        {
            if (id == right - 1)
            {
                std::cout << stack.at(id) << " }; ";
                newLine();
            }
            else
            {
                std::cout << stack.at(id) << " , ";
            }
        }
    }
    else
    {
        std::cout << "Invalid limits for the stack!";
        newLine();
    }
}

int main()
{
    auto nucleus = std::make_unique<ExperimentalData>();
    auto I = nucleus->spins.at(0);
    auto j = EnergyFormulae::jSP;
    auto spins = nucleus->spins;
    auto energies = nucleus->energies;

    double i1 = 89;
    double i2 = 12;
    double i3 = 48;
    double theta = -71;

    std::vector<double> thEnergies;
    // Fit::generateTheoreticalData(*nucleus, thEnergies, theta, i1, i2, i3);
    // std::cout << "Experiment vs. theory comparison"
    //           << "\n";
    // std::cout << "I    E_exp     E_th"
    //           << "\n";
    // for (int i = 0; i < spins.size(); ++i)
    // {
    //     std::cout << spins.at(i) << " " << energies.at(i) << " " << thEnergies.at(i) << "\n";
    // }
    // std::cout << "********** RMS **********"
    //           << "\n";
    // std::cout << Fit::rmsCalculation(energies, thEnergies) << "\n";

    // std::vector<double> thEnergies;
    // Fit::generateTheoreticalData(*nucleus, thEnergies, theta, i1, i2, i3);
    // for (double i = 0.5; i < 12.5; i+=1.0)
    // {
    //     auto omega = EnergyFormulae::omegaFreq(i, j, theta, i1, i2, i3);
    //     std::cout << i << " " << omega << "\n";
    // }

    // printArray_selector(energies, 0, 11);
    // newLine();
    // printArray_selector(energies, 11, 16);
    // newLine();
    // printArray_selector(energies, 16, 20);
    // newLine();
    // printArray_selector(thEnergies, 0, 11);
    // newLine();
    // printArray_selector(thEnergies, 11, 16);
    // newLine();
    // printArray_selector(thEnergies, 16, 20);

    // fit with fixed theta algorithm
    // Fit::getMinimum_RMS_fixedTheta(*nucleus, bestParams);

    //actual good fit algorithm
    auto bestParams = Fit::paramSet();
    auto startTime = std::chrono::high_resolution_clock::now();
    // Fit::getMinimum_RMS(*nucleus, bestParams);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "BEST RESULTS FOR THE THREE BANDS ARE:"
              << "\n";
    std::cout << "I1   I2   I3   THETA"
              << "\n";
    std::cout << bestParams.I1_min << "   " << bestParams.I2_min << "   " << bestParams.I3_min << "   " << bestParams.theta_min << "\n";
    std::cout << "ENERGY RMS: "
              << "\n";
    std::cout << bestParams.RMS_min << "\n";
    std::cout << "Process took " << static_cast<double>(duration / 1000000.0) << " seconds" << std::endl;

    // auto omegas = new EnergyFormulae::omegaTuple(5.5, j, bestParams.theta_min, bestParams.I1_min, bestParams.I2_min, bestParams.I3_min);
    // std::cout << omegas->omega << " " << omegas->omegaChiral << "\n";

    auto omegas = new EnergyFormulae::omegaTuple(9.5, 5.5, 30, 30, 100, 80);
    // std::cout << omegas->omega << " " << omegas->omegaChiral << "\n";
    auto omegasPrime = new EnergyFormulae::omegaPrimeTuple(9.5, 5.5, 30, 30, 100, 80);
    
    // std::cout << omegasPrime->omegaPrime << " " << omegasPrime->omegaPrimeChiral << "\n";

    // std::cout << EnergyFormulae::omegaFreq(9.5, 5.5, 30, 30, 100, 80) << "\n";
    // std::cout << EnergyFormulae::omegaFreqPrime(9.5, 5.5, 30, 30, 100, 80) << "\n";
}