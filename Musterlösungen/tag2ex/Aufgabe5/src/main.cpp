/*
 * main.cpp
 */

#include <iostream>
using namespace std;

#include <boost/make_shared.hpp>

#include "Building.h"

int main() {
	Building b(3);
	
	b.addWaitingPerson(0, boost::make_shared<Person>(2)); // person in floor 0 wants to floor 2
	b.addWaitingPerson(1, boost::make_shared<Person>(0)); // person in floor 1 wants to floor 0
	b.addWaitingPerson(2, boost::make_shared<Person>(0)); // person in floor 2 wants to floor 0
	        
	for (int f = 0; f < b.getNumberOfFLoors(); f++) {
		b.moveElevatorToFloor(f);
		b.letPopleIn();
		
		while (b.getElevator().getNumPeople() > 0) {
			b.moveElevatorToFloor(b.getElevator().getContainedPeople().front()->getDestinationFloor());
			b.removeArrivedPeople();
		}
	}

	cout << "Energy consumed: " << b.getElevator().getEnergyConsumed() << endl;
	
	return 0;
}
