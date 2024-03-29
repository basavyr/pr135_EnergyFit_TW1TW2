import numpy as np


class Utils:
    @staticmethod
    def generate_absolute_energy(egs: float, e: float) -> float:
        return round(e+egs, 3)

    @staticmethod
    def print_spins(spins: list[float]) -> None:
        for spin in spins:
            print(f'{int(spin*2)}/2')

    @staticmethod
    def print_energies(energies: list[float]) -> None:
        for e in energies:
            print(f'{round(e,3)}')


class Experimental:
    EGS = float(358.0 / 1000.0)  # the ground state energy (I=11/2 level)
    SGS = float(15 / 2)  # the ground spin state
    spin_1 = np.arange(SGS, 29.5, 2.0)
    spin_2 = np.arange(8.5, 18.5, 2.0)
    spin_3 = np.arange(9.5, 17.5, 2.0)
    energy_1_relative = [0.3729, 1.0327, 1.887, 2.8867, 3.9623,
                         4.806, 5.6403, 6.5225, 7.4449, 8.4019, 9.4069]
    energy_2_relative = [0.7466, 1.4731, 2.2688, 3.2245, 4.3362]
    energy_3_relative = [1.1971, 2.0237, 2.7875, 3.7965]

    def __init__(self) -> None:
        if self.is_ok() == False:
            print('Aborting operations. Check Experimental data!')
            exit(1)
        self.energy_1 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_1_relative]
        self.energy_2 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_2_relative]
        self.energy_3 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_3_relative]

    @classmethod
    def is_ok(self) -> bool:
        dif1 = len(self.spin_1) - len(self.energy_1_relative)
        dif2 = len(self.spin_2) - len(self.energy_2_relative)
        dif3 = len(self.spin_3) - len(self.energy_3_relative)
        if dif1 + dif2 + dif3 == 0:
            return True
        return False


class Theoretical():
    EGS = float(358.0 / 1000.0)  # the ground state energy (I=11/2 level)
    SGS = float(15 / 2)  # the ground spin state
    spin_1 = np.arange(SGS, 29.5, 2.0)
    spin_2 = np.arange(8.5, 18.5, 2.0)
    spin_3 = np.arange(9.5, 17.5, 2.0)

    energy_1_relative = [0.647553, 1.33931, 2.07514, 2.85499,
                         3.67883, 4.54665, 5.45844, 6.41421, 7.41393, 8.45762, 9.54528]
    energy_2_relative = [0.987917, 1.70172, 2.45956, 3.26141, 4.10724]
    energy_3_relative = [1.38737, 2.15942, 2.97568, 3.83604]

    def __init__(self) -> None:
        if self.is_ok() == False:
            print('Aborting operations. Check Theoretical data!')
            exit(1)
        self.energy_1 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_1_relative]
        self.energy_2 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_2_relative]
        self.energy_3 = [Utils.generate_absolute_energy(
            self.EGS, e) for e in self.energy_3_relative]

    @classmethod
    def is_ok(self) -> bool:
        dif1 = len(self.spin_1) - len(self.energy_1_relative)
        dif2 = len(self.spin_2) - len(self.energy_2_relative)
        dif3 = len(self.spin_3) - len(self.energy_3_relative)
        if dif1 + dif2 + dif3 == 0:
            return True
        return False


def main():
    exp_data = Experimental()
    th_data = Theoretical()

    print("\n")
    Utils.print_energies(exp_data.energy_1)
    print("\n")
    Utils.print_energies(th_data.energy_1)
    print("\n")

    print("\n")
    Utils.print_energies(exp_data.energy_2)
    print("\n")
    Utils.print_energies(th_data.energy_2)
    print("\n")

    print("\n")
    Utils.print_energies(exp_data.energy_3)
    print("\n")
    Utils.print_energies(th_data.energy_3)
    print("\n")


if __name__ == "__main__":
    main()
