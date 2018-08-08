#include <iostream>
#include <cstdlib>

#include "Building.h"
#include "ElevatorStrategy.h"
#include "EnergyMinimizingStrategy.h"

int main2() {
	Building hbi(6, new EnergyMinimizingStrategy());

	hbi.getElevator().moveToNextFloor();

	return 0;
}

int main2(int argc, char **argv){
	std::cout << argv[0] << std::endl;
	if (argc >= 2) {
		unsigned int levels = std::atoi(argv[1]);
		Building hbi(levels, new EnergyMinimizingStrategy());
		hbi.getElevator().moveToNextFloor();
	}
	else {
		Building hbi(3, new EnergyMinimizingStrategy());
		hbi.getElevator().moveToNextFloor();
	}
}
