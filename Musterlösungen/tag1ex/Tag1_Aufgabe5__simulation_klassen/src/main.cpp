/*
 * main.cpp
 */

#include <iostream>
using namespace std;

#include "Building.h"

int main() {
	Building b(3);
	
	b.addWaitingPerson(0, Person(2)); // person in floor 0 wants to floor 2
	b.addWaitingPerson(1, Person(0)); // person in floor 1 wants to floor 0
	b.addWaitingPerson(2, Person(0)); // person in floor 2 wants to floor 0
	        
	// check each floor
	for (int f = 0; f < b.getNumOfFloors(); f++) {
		b.moveElevatorToFloor(f);
		// collect all people at current floor
		b.letPeopleIn();
		
		// move each person to its destination and let it out
		while (b.getElevator().getNumPeople() > 0) {
			int dest = b.getElevator().getPerson(0).getDestinationFloor();
			b.moveElevatorToFloor(dest);
			b.removeArrivedPeople();
		}
	}

	cout << "Energy consumed: " << b.getElevator().getEnergyConsumed() << endl;
	
	return 0;
}
