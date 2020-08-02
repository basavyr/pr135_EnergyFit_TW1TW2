# The triaxial features of an odd nucleus -  General Workflow 

## The triaxial potential $V(q)$

The odd-A nucleus has a well defined energy, which in the present model is described by a set of physical quantities such as *moments of inertia*, single-particle angular momentum $j$, total spin of the nucleus itself $I$, the coupling angle between the odd-particle and the nucleus's one- and two-axes $\theta$.

These quantities are considered free parameters in this model, so, by solving the main goal of this work (which is that of reproducing the *excitation energies* of the wobbling spectrum of $^{135}$Pr), a fitting procedure is adopted, where one tries to find the values of the parameter set $P$ such that the deviations from experimental values are minimal.

Once the fitting procedure is finished, a proper set $P$ that best reproduces the experimental wobbling energies is obtained. However, careful analysis on the fitting parameters must be performed during the $RMS$ calculations:

* The wobbling frequencies obtained from these parameters must be physical quantities, both the frequency of the spin state $I$, as well as the one for its *chiral partner* (computed at a value of $\theta'=\theta+\pi$).
* The set $P$ must provide a physical form of the triaxial rotor potential $V(q)$. This is verified if the inertial factors $A,u,v_0,k$ verify some validity conditions which are given in the draft itself.
* The set $P$ is also used for computing the energy surface $\mathcal{H}$, which can be graphically represented as a contour plot. This shows the various wobbling regimes at different values of spins, and might indicate shape transitions (*phase transitions)*. The contour plot is carefully computed by verifying that the inertial factors discussed above are all valid quantities.

$$V(q)=F(I,A_1,A_2,A_3,j,\theta)$$

where $I$ and $j$ are known values and can be fixed *a-priori*. As a result $P\equiv[A_1,A_2,A_3,\theta]$.

### Quantization axes

Based on the moments of inertia's ordering, there can be three general cases on which the nucleus exhibits wobbling motion, and it can be represented as a special kind of motion, confined by the triaxial potential, which allows for the physical existence of its wobbling excitation states.

* 1-axis ordering: the maximal MOI is the one along 1-axis. Calculations are performed using 1-axis as the quantization axis.
* 2-axis ordering: the maximal MOI is the one along 2-axis. Calculations are performed using 2-axis as the quantization axis.
* 3-axis ordering: the maximal MOI is the one along 3-axis. Calculations are performed using 3-axis as the quantization axis.

Using all these quantization cases, the parameter set must verify that the inertial functions $A>0$ and $k=\sqrt{u}$.

Another condition is that the $u$ must be subunitary, or more precisely $u<1,u>-1,|u|\leq 1$.

The calculation of the energy surface implies prior knowledge of the MOI's ordering, the total spin state of the nucleus and the angular momentum of its odd particle.

Once these values are fixed, based on the fit parameters, the contour plot can be realized, representing the energy function in terms of spherical coordinates $(\theta,\varphi)$. The contour plot can provide relevant information regarding the actual type of *wobbling regime*, wether it is transverse or longitudinal, or wether the nucleus is rotating in one of the local minimum points, or a global minimum.

Regarding the actual fitting procedure, a Notability diagram will be added in the source documentation. 
