#include <iostream>

#include "../include/expdata.h"
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
    // auto x = new ExperimentalData;
    auto x = std::make_unique<ExperimentalData>();
    // for (auto id = 0; id < x->energies.size(); ++id)
    // {
    //     std::cout << x->energies.at(id) << " ";
    // }
    newLine();
    testApp();
}