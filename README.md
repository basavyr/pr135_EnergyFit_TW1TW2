# Calculating the excitation energies for the wobbling spectra of $^{135}$Pr

Author: Robert Poenaru

E-mail: robert.poenaru@drd.unibuc.ro

- [Calculating the excitation energies for the wobbling spectra of $^{135}$Pr](#calculating-the-excitation-energies-for-the-wobbling-spectra-of-mathsemanticsmrowmsupmrowmrowmn135mnmsupmrowannotation-encodingapplicationx-tex135annotationsemanticsmath135pr)
  - [Least-squares-fit procedure for getting the $E_\text{RMS}$ and the free parameters](#least-squares-fit-procedure-for-getting-the-mathsemanticsmrowmsubmiemimtextrmsmtextmsubmrowannotation-encodingapplicationx-texe_textrmsannotationsemanticsmatherms-and-the-free-parameters)
  - [Details on the problem](#details-on-the-problem)
  - [Structure of the code](#structure-of-the-code)
    - [Time measurement](#time-measurement)
  - [Potential fit results](#potential-fit-results)
  - [Observation:](#observation)

## Least-squares-fit procedure for getting the $E_\text{RMS}$ and the free parameters  

## Details on the problem

* The model has 5 free parameters: 
  * 3 inertia factors: $A_1,A_2,A_3$
  * the single particle potential strength $V$
  * the coupling angle $\theta$
* The experimental data set contains:
  * The yrast band Y0
  * The *one-phonon* wobbling band TW1
  * The (new) *two-phonon* wobbling band TW2. Experimentally confirmed in the recent work of Sensharma et al.[^1]

[^1]: Sensharma, N., et al. "Two-phonon wobbling in 135Pr." Physics Letters B 792 (2019): 170-174.

## Structure of the code

This `C++` project is structured as follows:

+ The **include** folder has the necessary header files for serving the experimental data 
  * `energyFormulas.h` - Calculating the energies for each band (numerical expressions) as a function of the input parameters 
  * `expData.h` - Serves the experimental data to the main algorithm. Experimental data consists in the energy states for the three triaxial bands (namely Y0,TW1 and TW2). Units are in MeV (if not, a transformation method will be provided in the header). **Algorithm works with EXCITATION energies**. So the first state from Y0 will be subtracted.
  * `fitProcedure.h` - The methods for calculating an RMS as a function of the free parameters and also a minimization procedure to find the best RMS value.
* The **cc** directory which includes:
  * `energyFormulas.cpp` 
  * `main.cpp` 
  * `fitProcedure.cpp`
 
 ### Time measurement

 The main `Fit` class has an instrument for measuring the time execution of any object which is instantiated by the user through a smart point (i.e. *unique pointer* or *shared pointer*)

  * `make_unique`
  * `make_shared`

The class `Fit` -> private variable to store the start point (when object is created via the default constructed).
The method `measureTime()` gives the total execution time of the class object on the main thread when it stops (through the default destructor).

## Potential fit results

![](/reports/images/2020-03-20-12-39-29.png)

These are the fit parameters obtained within the new `C++` algorithm which includes the confirmed two-phonon wobbling band `TW2`.

Searching for the best RMS finished...  
Total number of iterations= 793117000  
BEST RESULTS FOR THE THREE BANDS ARE:  
I1   I2   I3   THETA  
89   12   48   -71  
ENERGY RMS:   
0.174452  

## Observation:

It seems that for the obtained fit parameters, the wobbling frequencies calculated for a chiral transformation (i.e. rotated system with an angle $\pi$), the quantity under the square root in the expression of $\omega^I$ becomes negative, which results in a **complex value**
> **For these parameters, small spins might provide non-physical solutions!**