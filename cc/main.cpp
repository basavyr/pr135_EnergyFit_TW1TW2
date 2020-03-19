#include <iostream>

#include "../include/expdata.h"
#include "../include/energyFormulas.h"
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

int main()
{
    auto x = std::make_unique<ExperimentalData>();
    auto I = x->spins.at(0);
    auto j = EnergyFormulae::jSP;
    auto spins = x->spins;
    auto energies = x->energies;

    double i1 = 129;
    double i2 = 3;
    double i3 = 52;
    double theta = -160;
    for (auto id = 0; id < ExperimentalData::yrast0.size()-1; ++id)
    {
        auto I = spins.at(id);
        auto currentValue = EnergyFormulae::yrast0(I, j, theta, i1, i2, i3);
        std::cout << spins.at(id) << " " << energies.at(id) << " " << currentValue << "\n";
    }
}