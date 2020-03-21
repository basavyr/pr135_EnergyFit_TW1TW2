#include "../include/energyFormulas.h"

double EnergyFormulae::jComponent(int k, double oddSpin, double theta)
{
    //work with theta in degrees (default input value is RAD)
    auto thetaDegrees = static_cast<double>(theta * PI / 180.0);
    auto j1 = oddSpin * cos(thetaDegrees);
    auto j2 = oddSpin * sin(thetaDegrees);
    if (k == 1)
        return j1;
    return j2;
}

double EnergyFormulae::inertiaFactor(double moi)
{
    if (!moi)
        return 6969;
    auto a = static_cast<double>(1 / (2 * moi));
    return a;
}

double EnergyFormulae::omegaFreq(double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    auto a1 = EnergyFormulae::inertiaFactor(i1);
    auto a2 = EnergyFormulae::inertiaFactor(i2);
    auto a3 = EnergyFormulae::inertiaFactor(i3);
    //stop of the inertia moments are invalid
    if (a1 == 6969 || a2 == 6969 || a3 == 6969)
        return 6969;

    auto j1 = EnergyFormulae::jComponent(1, oddSpin, theta);
    auto j2 = EnergyFormulae::jComponent(2, oddSpin, theta);
    auto I = spin;

    auto term1 = (2.0 * I + 1.0) * (a2 - a1 - static_cast<double>((a2 * j2) / I)) - 2.0 * a1 * j1;
    auto term2 = (2.0 * I + 1) * (a3 - a1) - 2.0 * a1 * j1;
    auto term3 = (a3 - a1) * (a2 - a1 - static_cast<double>((a2 * j2) / I));
    if (isnan(term1) || isnan(term2) || isnan(term3))
        return 6969;
    auto omega = sqrt(term1 * term2 - term3);
    if (!isnan(omega))
        return omega;
    return 6969;
}

double EnergyFormulae::excitationEnergy(int n, double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    //finish calculus immediately if omega is not a valid number
    // auto omega = EnergyFormulae::omegaFreq(spin, oddSpin, theta, i1, i2, i3);
    // if (isnan(omega))
    //     return 6969;

    //generate the tuple with chiral frequencies (omega and omegachiral)
    auto omegas = new EnergyFormulae::omegaTuple(spin, oddSpin, theta, i1, i2, i3);
    //stop if one of the frequencies is complex
    if (omegas->omega == 6969 || omegas->omegaChiral == 6969)
        return 6969;

    auto a1 = EnergyFormulae::inertiaFactor(i1);
    auto a2 = EnergyFormulae::inertiaFactor(i2);
    auto a3 = EnergyFormulae::inertiaFactor(i3);
    //stop of the inertia moments are invalid
    if (a1 == 6969 || a2 == 6969 || a3 == 6969)
        return 6969;

    auto j1 = EnergyFormulae::jComponent(1, oddSpin, theta);
    auto j2 = EnergyFormulae::jComponent(2, oddSpin, theta);
    auto I = spin;

    auto squaredSum = a1 * pow(j1, 2) + a2 * pow(j2, 2);
    auto minTerm = a1 * pow(I, 2) + (2.0 * I + 1.0) * a1 * j1 - I * a2 * j2 + squaredSum;
    auto wobblingQuanta_n = omegas->omega * (n + 0.5);
    auto energy_n = minTerm + wobblingQuanta_n;
    if (!isnan(energy_n))
        return energy_n;
    return 6969;
}

double EnergyFormulae::yrast0(double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    auto e0 = EnergyFormulae::excitationEnergy(0, EnergyFormulae::spinZero, EnergyFormulae::jSP, theta, i1, i2, i3);
    //continue only if the bandhead energy is a valid number
    if (isnan(e0))
        return 6969;
    auto I = spin;
    auto j = oddSpin;

    auto eYrast_I = EnergyFormulae::excitationEnergy(0, I, j, theta, i1, i2, i3);
    if (!isnan(eYrast_I))
        return eYrast_I - e0;
    return 6969;
}

double EnergyFormulae::tw1(double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    auto e0 = EnergyFormulae::excitationEnergy(0, EnergyFormulae::spinZero, EnergyFormulae::jSP, theta, i1, i2, i3);
    //continue only if the bandhead energy is a valid number
    if (isnan(e0))
        return 6969;
    auto I = spin;
    auto j = oddSpin;

    auto eTW1_I = EnergyFormulae::excitationEnergy(0, I, j, theta, i1, i2, i3);
    if (!isnan(eTW1_I))
        return eTW1_I - e0;
    return 6969;
}

double EnergyFormulae::tw2(double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    auto e0 = EnergyFormulae::excitationEnergy(0, EnergyFormulae::spinZero, EnergyFormulae::jSP, theta, i1, i2, i3);
    //continue only if the bandhead energy is a valid number
    if (isnan(e0))
        return 6969;
    auto I = spin;
    auto j = oddSpin;

    //work with I-1
    //any I state from TW2 is built on top of TW1 with a 1-phonon energy from the state I-1
    auto eTW2_I = EnergyFormulae::excitationEnergy(1, I - 1, j, theta, i1, i2, i3);
    if (!isnan(eTW2_I))
        return eTW2_I - e0;
    return 6969;
}

EnergyFormulae::omegaTuple EnergyFormulae::omegaTupleCalculation(double spin, double oddSpin, double theta, double i1, double i2, double i3)
{
    auto thetaPlusPi = theta + 180.0;
    auto I = spin;
    auto j = oddSpin;
    auto result = new omegaTuple(I, j, theta, i1, i2, i3);
    ;
    // result->omega = EnergyFormulae::omegaFreq(I, j, theta, i1, i2, i3);
    // result->omegaChiral = EnergyFormulae::omegaFreq(I, j, thetaPlusPi, i1, i2, i3);
    if (result->omega == 6969 || result->omegaChiral == 6969)
    {
        std::cout << "One of the two wobbling frequencies is COMPLEX!!!"
                  << "\n";
        result->omega = 6969;
        result->omegaChiral = 6969;
        return *result;
    }
    return *result;
}