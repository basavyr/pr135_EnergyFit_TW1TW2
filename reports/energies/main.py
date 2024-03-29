import numpy as np


class Experimental:
    EGS = float(358.0 / 1000.0)  # the ground state energy (I=11/2 level)
    SGS = float(11 / 2)  # the ground spin state
    spin_1 = np.arange(SGS, 29.5, 2.0)
    spin_2 = np.arange(8.5, 18.5, 2.0)
    spin_3 = np.arange(9.5, 17.5, 2.0)
    energy_1_relative = [0, 0.3729, 1.0327, 1.887, 2.8867, 3.9623,
                         4.806, 5.6403, 6.5225, 7.4449, 8.4019, 9.4069]
    energy_2_relative = [0.7466, 1.4731, 2.2688, 3.2245, 4.3362]
    energy_3_relative = [1.1971, 2.0237, 2.7875, 3.7965]

    def __init__(self) -> None:
        self.energy_1 = [self.generate_absolute_energy(
            e) for e in self.energy_1_relative]
        self.energy_2 = [self.generate_absolute_energy(
            e) for e in self.energy_2_relative]
        self.energy_3 = [self.generate_absolute_energy(
            e) for e in self.energy_3_relative]

    @classmethod
    def is_ok(self) -> bool:
        dif1 = len(self.spin_1) - len(self.energy_1_relative)
        dif2 = len(self.spin_2) - len(self.energy_2_relative)
        dif3 = len(self.spin_3) - len(self.energy_3_relative)
        if dif1 + dif2 + dif3 == 0:
            return True
        return False

    @classmethod
    def generate_absolute_energy(self, e: float) -> float:
        return e+self.EGS


def main():
    exp_data = Experimental()


if __name__ == "__main__":
    main()
