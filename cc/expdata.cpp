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
    return returnable;
}

std::vector<double> ExperimentalData::init_tw1()
{
    std::vector<double> gammas = {726.5, 795.7, 955.7, 1111.7};
    std::vector<double> returnable;
    return returnable;
}

std::vector<double> ExperimentalData::init_tw2()
{
    std::vector<double> gammas = {826.6, 763.8, 1009.0};
    std::vector<double> returnable;
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
}
ExperimentalData::~ExperimentalData()
{
    std::cout << "FINISHED..." << std::endl;
}