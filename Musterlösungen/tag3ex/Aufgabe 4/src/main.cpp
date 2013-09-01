/*
 * main.cpp
 */

#include <iostream>
using namespace std;

#include <boost/make_shared.hpp>

#include "Building.h"
#include "Simulation.h"
#include "SimpleElevatorStrategy.h"
#include "EnergySavingStrategy.h"

#include <ctime>

int main() {
	srand(time(NULL));
	const int numFloors = 8;
	const int numPeople = 20;
	Building b(numFloors);
	
	// randomy add some people
	for (int i = 0; i < numPeople; i++)
		b.getFloor(rand() % numFloors).addWaitingHuman(boost::make_shared<Person>(rand() % numFloors));
	
	Building b2(b);
	
	EnergySavingStrategy strat;
	SimpleElevatorStrategy strat2;
	int floors1 = runSimulation(b, strat).size();
	int floors2 = runSimulation(b2, strat2).size();
	
	cout << "\t\t      energy  stops" << endl;
	cout << "simple strategy:\t" << b2.getElevator().getEnergyConsumed() << "\t" << floors2 << endl;
	cout << "optimal strategy:\t" << b.getElevator().getEnergyConsumed() << "\t" << floors1 << endl;
	
	return 0;
}
