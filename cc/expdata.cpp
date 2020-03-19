#include "../include/expdata.h"

std::vector<double> ExperimentalData::init_spin0()
{
    std::vector<double> spins = {5.5, 7.5, 9.5, 11.5, 13.5, 15.5, 17.5, 19.5, 21.5, 23.5, 25.5, 27.5};
    std::vector<double> returnable;
    for (auto x = 0; x < spins.size(); ++x)
    {
        returnable.emplace_back(std::move(spins.at(x)));
    }
    return returnable;
}

std::vector<double> ExperimentalData::init_spin1()
{
    std::vector<double> spins = {8.5, 10.5, 12.5, 14.5, 16.5};
    std::vector<double> returnable;
    for (auto x = 0; x < spins.size(); ++x)
    {
        returnable.emplace_back(std::move(spins.at(x)));
    }
    return returnable;
}

std::vector<double> ExperimentalData::init_spin2()
{
    std::vector<double> spins = {9.5, 11.5, 13.5, 15.5};
    std::vector<double> returnable;
    for (auto x = 0; x < spins.size(); ++x)
    {
        returnable.emplace_back(std::move(spins.at(x)));
    }
    return returnable;
}

std::vector<double> ExperimentalData::init_yrast0()
{
    std::vector<double> gammas = {372.9, 659.8, 854.3, 999.7, 1075.6, 843.7, 834.3, 882.2, 922.4, 957.0, 1005.0};
    std::vector<double> returnable;

    //the energy of the first level in YRAST0
    double bandhead = ExperimentalData::gse;
    //transform in MeV
    bandhead = static_cast<double>(bandhead / 1000);

    returnable.emplace_back(bandhead);
    for (int i = 0; i < gammas.size(); ++i)
    {
        //transform in MeV
        auto x = returnable.at(i) + static_cast<double>(gammas.at(i) / 1000);
        returnable.emplace_back(x);
    }

    return returnable;
}

std::vector<double> ExperimentalData::init_tw1()
{
    std::vector<double> gammas = {726.5, 795.7, 955.7, 1111.7};
    std::vector<double> returnable;

    //the energy for the transition TW1->Y0
    const double transToYrast = 746.6;

    //the energy of the first level in TW1
    double bandhead;
    bandhead = ExperimentalData::gse + transToYrast;
    //transform in MeV
    bandhead = static_cast<double>(bandhead / 1000);

    returnable.emplace_back(bandhead);
    for (int i = 0; i < gammas.size(); ++i)
    {
        //transform in MeV
        auto x = returnable.at(i) + static_cast<double>(gammas.at(i) / 1000);
        returnable.emplace_back(x);
    }

    return returnable;
}

std::vector<double> ExperimentalData::init_tw2()
{
    std::vector<double> gammas = {826.6, 763.8, 1009.0};
    std::vector<double> returnable;

    //the energy for the transition TW2->Y0
    const double transToYrast = 1197.1;

    double bandhead;
    bandhead = ExperimentalData::gse + transToYrast;
    //transform in MeV
    bandhead = static_cast<double>(bandhead / 1000);

    returnable.emplace_back(bandhead);
    for (int i = 0; i < gammas.size(); ++i)
    {
        //transform in MeV
        auto x = returnable.at(i) + static_cast<double>(gammas.at(i) / 1000);
        returnable.emplace_back(x);
    }

    return returnable;
}

//create the static spin containers
std::vector<double> ExperimentalData::spin0 = ExperimentalData::init_spin0();
std::vector<double> ExperimentalData::spin1 = ExperimentalData::init_spin1();
std::vector<double> ExperimentalData::spin2 = ExperimentalData::init_spin2();

//create the static energy containers
std::vector<double> ExperimentalData::yrast0 = ExperimentalData::init_yrast0();
std::vector<double> ExperimentalData::tw1 = ExperimentalData::init_tw1();
std::vector<double> ExperimentalData::tw2 = ExperimentalData::init_tw2();

ExperimentalData::ExperimentalData()
{
    generateData(spins, energies);
}
ExperimentalData::~ExperimentalData()
{
}

void ExperimentalData::arrayPrinter(std::vector<double> &array)
{
    for (auto &&n : array)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void ExperimentalData::generateData(std::vector<double> &spins, std::vector<double> &energies)
{
    const double e0 = ExperimentalData::yrast0.at(0);
    //generate the TOTAL spin container
    for (int i = 1; i < ExperimentalData::spin0.size(); ++i)
    {
        spins.emplace_back(spin0.at(i));
    }
    for (int i = 0; i < ExperimentalData::spin1.size(); ++i)
    {
        spins.emplace_back(spin1.at(i));
    }
    for (int i = 0; i < ExperimentalData::spin2.size(); ++i)
    {
        spins.emplace_back(spin2.at(i));
    }
    //generate the TOTAL energy container
    for (int i = 1; i < ExperimentalData::yrast0.size(); ++i)
    {
        energies.emplace_back(yrast0.at(i) - e0);
    }
    for (int i = 0; i < ExperimentalData::tw1.size(); ++i)
    {
        energies.emplace_back(tw1.at(i) - e0);
    }
    for (int i = 0; i < ExperimentalData::tw2.size(); ++i)
    {
        energies.emplace_back(tw2.at(i) - e0);
    }
}