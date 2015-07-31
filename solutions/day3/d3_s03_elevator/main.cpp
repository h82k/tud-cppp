#include <boost/make_shared.hpp>
#include "Building.hpp"
#include "Simulation.hpp"
#include "SimpleElevatorStrategy.hpp"
#include "EnergySavingStrategy.hpp"
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));
	const int numFloors = 8;
	const int numPeople = 20;
	Building b(numFloors);
	
	// randomly add some people
	for (int i = 0; i < numPeople; ++i) {
		b.addWaitingPerson(rand() % numFloors, boost::make_shared<Person>(rand() % numFloors));
	}
	Building b2(b);
	EnergySavingStrategy strat;
	SimpleElevatorStrategy strat2;
	int floors1 = runSimulation(b, strat).size();
	int floors2 = runSimulation(b2, strat2).size();
	
	cout << "\t\t      energy  stops" << endl;
	cout << "simple strategy:\t" << b2.getElevator().getEnergyConsumed() << "\t" << floors2 << endl;
	cout << "optimal strategy:\t" << b.getElevator().getEnergyConsumed() << "\t" << floors1 << endl;
}
