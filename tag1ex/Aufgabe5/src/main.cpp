/*
 * main.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: jgdo
 */

#include <iostream>
using namespace std;

#include "Building.h"

int main() {
	Building b(3);
	
	b.getFloor(0).addWaitingHuman(Person(2)); // person in floor 0 wants to floor 2
	b.getFloor(1).addWaitingHuman(Person(0)); // person in floor 1 wants to floor 0
	b.getFloor(2).addWaitingHuman(Person(0)); // person in floor 2 wants to floor 0
	        
	for (int f = 0; f < b.getNumberOfFLoors(); f++) {
		b.getElevator().moveToFloor(f);
		
		b.getElevator().addPeople(b.getFloor(f).removeAllPeople());
		while (b.getElevator().getNumPeople() > 0) {
			b.getElevator().moveToFloor(b.getElevator().getHuman(0).destinationFloor());
			b.getElevator().removeArrivedPeople();
		}
	}

	cout << "Energy consumed: " << b.getElevator().engergyConsumed() << endl;
	
	return 0;
}
