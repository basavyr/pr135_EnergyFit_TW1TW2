#include "../include/fitProcedure.h"
// #include "../include/expdata.h"
#include "../include/energyFormulas.h"

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

    //fill the YRAST BAND
    for (auto id = 0; id < yrastSize; ++id)
    {
        auto spin = obj.spins.at(id);
    }

    //fill the TW1 BAND
    for (auto id = yrastSize; id < tw1Size + yrastSize; ++id)
    {
        auto spin = obj.spins.at(id);
    }

    //fill the TW2 BAND
    for (auto id = tw1Size + yrastSize; id < tw1Size + yrastSize + tw2Size; ++id)
    {
        auto spin = obj.spins.at(id);
    }
}