/*
 * main.cpp
 */

#include <iostream>
using namespace std;

#include "Building.h"

int main() {
	Building b(3);
	
	b.getFloor(0).addWaitingPerson(Person(2)); // person in floor 0 wants to floor 2
	b.getFloor(1).addWaitingPerson(Person(0)); // person in floor 1 wants to floor 0
	b.getFloor(2).addWaitingPerson(Person(0)); // person in floor 2 wants to floor 0
	
	// check each floor
	for (int f = 0; f < b.getNumOfFloors(); f++) {
		b.getElevator().moveToFloor(f);
		// collect all people at current floor
		b.getElevator().addPeople(b.getFloor(f).removeAllPeople());
		
		// move each person to its destination and let it out
		while (b.getElevator().getNumPeople() > 0) {
			b.getElevator().moveToFloor(b.getElevator().getPerson(0).getDestinationFloor());
			b.getElevator().removeArrivedPeople();
		}
	}

	cout << "Energy consumed: " << b.getElevator().getEngergyConsumed() << endl;
	
	return 0;
}
