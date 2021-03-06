#ifndef EXPDATA_HH
#define EXPDATA_HH

#include <vector>
#include <iostream>

class ExperimentalData
{
    //default constructors
public:
    ExperimentalData();
    ~ExperimentalData();
    static void arrayPrinter(std::vector<double> &);
    static void generateData(std::vector<double> &, std::vector<double> &);
    //3-FOLD CONTAINERS TO HOLD THE EXPERIMENTAL SPINS AND ENERGIES
    std::vector<double> spins;
    //3-FOLD CONTAINERS TO HOLD THE EXPERIMENTAL SPINS AND ENERGIES
    //THESE ARE THE EXCITATION ENERGIES
    std::vector<double> energies;

public:
    //the ground state energy (E0->Y0)
    static constexpr double gse = 358.0;

    //init functions for arrays
public:
    static std::vector<double> init_spin0();
    static std::vector<double> init_spin1();
    static std::vector<double> init_spin2();
    static std::vector<double> init_yrast0();
    static std::vector<double> init_tw1();
    static std::vector<double> init_tw2();

    //containers for storing the spins and experimental energies
public:
    //spin sequence for the yrast band
    static std::vector<double> spin0;
    //spin sequence for the one-phonon wobbling band
    static std::vector<double> spin1;
    //spin sequence for the two-phonon wobbling band
    static std::vector<double> spin2;

    //EXCITATION ENERGIES
    //energies for the yrast band
    static std::vector<double> yrast0;
    //EXCITATION ENERGIES
    //energies for the one-phonon wobbling band
    static std::vector<double> tw1;
    //EXCITATION ENERGIES
    //energies for the two-phonon wobbling band
    static std::vector<double> tw2;
};

#endif // EXPDATA_HH
