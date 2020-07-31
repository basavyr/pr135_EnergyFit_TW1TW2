#include <cmath>
#include <vector>
#include <iostream>

//ESCAPE NUMBER  = 6969

class EnergyFormulae
{
public:
    //create the omega tuple for storing both the wobbling frequency and its chiral partner
    struct omegaTuple
    {
        double omega;
        double omegaChiral;
        omegaTuple(double spin, double oddSpin, double theta, double i1, double i2, double i3)
        {
            auto I = spin;
            auto j = oddSpin;
            auto thetaPlusPi = theta + 180;
            omega = EnergyFormulae::omegaFreq(I, j, theta, i1, i2, i3);
            omegaChiral = EnergyFormulae::omegaFreq(I, j, thetaPlusPi, i1, i2, i3);
        }
    };

public:
    static constexpr double PI = 3.14159265358979;
    //oddSpin
    //the single particle angular momentum (odd Particle)
    static constexpr double jSP = 5.5;
    //the spin of the bandhead:)
    static constexpr double spinZero = 5.5;
    //theta = RAD
    static double jComponent(int k, double oddSpin, double theta);
    static double inertiaFactor(double moi);
    //theta = RAD
    //this is the Wobbling frequency which corresponds to the global minimum
    //in our case, the global minimum was located initially at q=±2K,4K
    //the local minima is located to other points q=0
    //the wobbling frequency for the local minima is denoted in the draft with omegaprime (formula 4.6 in the draft)
    static double omegaFreq(double spin, double oddSpin, double theta, double i1, double i2, double i3);
    static double omegaFreqPrime(double spin, double oddSpin, double theta, double i1, double i2, double i3);
    static omegaTuple omegaTupleCalculation(double spin, double oddSpin, double theta, double i1, double i2, double i3);

    //define the energy expressions (analytical formulae for the theoretical energies)
    //working with excitation energies (normalized to the bandhead from yrast0)
public:
    //The first energy band - YRAST0 analytical expression
    //theta = RAD
    static double
    yrast0(double spin, double oddSpin, double theta, double i1, double i2, double i3);
    //The second energy band - TW1 analytical expression
    //The one-phonon wobbling band
    //theta = RAD
    static double tw1(double spin, double oddSpin, double theta, double i1, double i2, double i3);
    //The third energy band - TW2 analytical expression
    //The two-phonon wobbling band
    //theta = RAD
    static double tw2(double spin, double oddSpin, double theta, double i1, double i2, double i3);
    static double excitationEnergy(int n, double spin, double oddSpin, double theta, double i1, double i2, double i3);

    //defining the helper functions
public:
    static double inertiaFunction(double spin, double oddSpin, double theta, double a1, double a2);
    static double u(double spin, double oddSpin, double theta, double a1, double a2, double a3);
    static double v0(double spin, double oddSpin, double theta, double a1, double a2, double a3);
};