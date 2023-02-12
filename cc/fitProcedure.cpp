#include "../include/fitProcedure.h"
// #include "../include/expdata.h"
#include "../include/energyFormulas.h"

const std::string before = "Before validity condition!\n";
const std::string after = "Valid parameters!\n";

// declare the inertial functions
// A-inertial parameter
double Fit::AFunction(double spin, double I1, double I2, double oddSpin, double theta)
{
    auto A1 = EnergyFormulae::inertiaFactor(I1);
    auto A2 = EnergyFormulae::inertiaFactor(I2);
    auto I = spin;
    auto j2 = EnergyFormulae::jComponent(2, oddSpin, theta);
    auto A = static_cast<double>(A2 * (1.0 - j2 / I) - A1);
    return A;
}
// u-inertial parameter
double Fit::uFunction(double spin, double I1, double I2, double I3, double oddSpin, double theta)
{
    auto A1 = EnergyFormulae::inertiaFactor(I1);
    auto A3 = EnergyFormulae::inertiaFactor(I3);
    auto diff = A3 - A1;
    auto A = Fit::AFunction(spin, I1, I2, oddSpin, theta);
    auto u = static_cast<double>(diff / A);
    return u;
}
// the k-parameter (function of u-inertial parameter)
double Fit::kFunction(double spin, double I1, double I2, double I3, double oddSpin, double theta)
{
    auto u = uFunction(spin, I1, I2, I3, oddSpin, theta);
    return sqrt(abs(u));
}

// define the function  that checks for valid condition  on the fitting parameters
// A must be positive
// u must be between 0 and 1
double Fit::ValidConditions(double I, double I1, double I2, double I3, double oddSpin, double theta)
{
    auto j = oddSpin;
    auto A = Fit::AFunction(I, I1, I2, j, theta);
    auto u = Fit::uFunction(I, I1, I2, I3, j, theta);
    auto k = Fit::kFunction(I, I1, I2, I3, j, theta);
    bool ok_A = false;
    bool ok_u = false;
    if (A >= 0.00)
        ok_A = true;
    if (u > 0.0 && u < 1.0)
        ok_u = true;
    if (ok_u && ok_A)
        return 1;
    return 0;
}

double Fit::ValidConditions_Direct(double A, double u)
{
    bool ok_A = false;
    bool ok_u = false;
    if (A >= 0.00)
        ok_A = true;
    if (u > 0.0 && u < 1.0)
        ok_u = true;
    if (ok_u && ok_A)
        return 1;
    return 0;
}

double Fit::Validity_FullSpinRange(double I1, double I2, double I3, double oddSpin, double theta)
{
    int counter = 0;
    auto spinHead = 5.5;
    auto spinEnd = 22.5;
    auto spinStep = 2.0;
    std::vector<double> spinSeq;
    for (auto i = spinHead; i <= spinEnd; i += spinStep)
    {
        spinSeq.emplace_back(i);
    }
    for (auto &&spin : spinSeq)
    {
        if (ValidConditions(spin, I1, I2, I3, oddSpin, theta) == 1)
        {
            counter++;
            // std::cout << "ok for this spin and params"<< "\n";
        }
    }
    if (counter == spinSeq.size())
        return 1;
    return 0;
}

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
    // stop if the arrays have different sizes
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
    // fill the YRAST BAND
    for (auto id = 0; id < yrastSize; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::yrast0(I, j, theta, i1, i2, i3);
        // only add valid numbers
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

    // fill the TW1 BAND
    for (auto id = yrastSize; id < tw1Size + yrastSize; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::tw1(I, j, theta, i1, i2, i3);
        // only add valid numbers
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

    // fill the TW2 BAND
    for (auto id = tw1Size + yrastSize; id < tw1Size + yrastSize + tw2Size; ++id)
    {
        auto I = obj.spins.at(id);
        auto energy_I = EnergyFormulae::tw2(I, j, theta, i1, i2, i3);
        // only add valid numbers
        if (energy_I != 6969)
        {
            finalStack.emplace_back(energy_I);
            errorchecker++;
        }
    }
    // check if the generated array has the correct size;
    if (errorchecker != totalSize)
        std::cout << "SHOULD FAIL IN RMS CALCULATION..."
                  << "\n";
}

void Fit::getMinimum_RMS(ExperimentalData &obj, paramSet &bestParams)
{
    paramLimits limits;

    // get the experimental results from the class-object
    auto expEnergies = obj.energies;

    double minval = 9876543210.123;

    int noIterations = 0;
    // start searching for the minimum rms
    for (double i1 = limits.I_left; i1 <= limits.I_right; i1 += limits.I_step)
    {
        for (double i2 = limits.I_left; i2 <= limits.I_right; i2 += limits.I_step)
        {
            for (double i3 = limits.I_left; i3 <= limits.I_right; i3 += limits.I_step)
            {
                for (double theta = limits.theta_left; theta <= limits.theta_right; theta += limits.theta_step)

                {
                    // generate the theoretical stack
                    std::vector<double> thEnergies;

                    //! the place where a validity condition for the fit parameters must be introduced
                    // std::cout << before;
                    if (!Validity_FullSpinRange(i1, i2, i2, EnergyFormulae::jSP, theta))
                    {
                        // std::cout << "Invalid params!"<< "\n";
                        break;
                    }
                    // std::cout << "After the validity condition"<<"\n";

                    // populate the theoretical energies stack
                    Fit::generateTheoreticalData(obj, thEnergies, theta, i1, i2, i3);

                    // calculate the rms with the current generated excitation energies
                    auto currentRMS = rmsCalculation(expEnergies, thEnergies);

                    // store the value (if less then current minval)
                    if (currentRMS <= minval && currentRMS != 6969)
                    {
                        minval = currentRMS;
                        bestParams.I1_min = i1;
                        bestParams.I2_min = i2;
                        bestParams.I3_min = i3;
                        bestParams.theta_min = theta;
                        bestParams.RMS_min = minval;
                    }
                    // count the iterations
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

    // get the experimental results from the class-object
    auto expEnergies = obj.energies;

    double minval = 9876543210.123;
    const double theta = 109;

    int noIterations = 0;
    // start searching for the minimum rms
    for (double i1 = limits.I_left; i1 <= limits.I_right; i1 += limits.I_step)
    {
        for (double i2 = limits.I_left; i2 <= limits.I_right; i2 += limits.I_step)
        {
            for (double i3 = limits.I_left; i3 <= limits.I_right; i3 += limits.I_step)
            {
                // generate the theoretical stack
                std::vector<double> thEnergies;

                // populate the theoretical energies stack
                Fit::generateTheoreticalData(obj, thEnergies, theta, i1, i2, i3);

                // calculate the rms
                auto currentRMS = rmsCalculation(expEnergies, thEnergies);

                // store the value (if less then current minval)
                if (currentRMS <= minval && currentRMS != 6969)
                {
                    minval = currentRMS;
                    bestParams.I1_min = i1;
                    bestParams.I2_min = i2;
                    bestParams.I3_min = i3;
                    bestParams.RMS_min = minval;
                }
                // count the iterations
                noIterations++;
            }
        }
    }
    std::cout << "Searching for the best RMS finished..."
              << "\n";
    std::cout << "Total number of iterations= " << noIterations << "\n";
}