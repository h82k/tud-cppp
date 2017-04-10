#include "Building.hpp"
#include "Simulation.hpp"
#include "SimpleElevatorStrategy.hpp"
#include "EnergySavingStrategy.hpp"
#include <ctime>
#include <iostream>

int main() {
	srand(time(NULL));
	const int numFloors = 8;
	const int numPeople = 20;
	Building b(numFloors);
	
	// randomly add some people
	for (int i = 0; i < numPeople; ++i) {
		b.addWaitingPerson(rand() % numFloors, std::make_shared<Person>(rand() % numFloors));
	}
	Building b2(b);
	EnergySavingStrategy strat;
	SimpleElevatorStrategy strat2;
	int floors1 = runSimulation(b, strat).size();
	int floors2 = runSimulation(b2, strat2).size();
	
	std::cout << "\t\t      energy  stops" << std::endl;
	std::cout << "simple strategy:\t" << b2.getElevator().getEnergyConsumed() << "\t" << floors2 << std::endl;
	std::cout << "optimal strategy:\t" << b.getElevator().getEnergyConsumed() << "\t" << floors1 << std::endl;
}
