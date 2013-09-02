/* Building.cpp  */


#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>

#include "Building.h"


Building::Building(int numberOfFloors,
		           ConstElevatorStrategyPtr strategy):
		floors(numberOfFloors, Floor(0)),
		elevator(&floors[0], strategy)
{
	for (int i = 0; i < numberOfFloors; i++)
		floors[i].setNumber(i);

	cout << "Building(...): "
		 << "Creating building with "
		 << numberOfFloors
		 << " floors." << endl;

	cout << "Building(...): "
		 << "Elevator is on Floor: "
		 << elevator.getCurrentFloor()->getNumber()
		 << endl;
}

Building::~Building() {
	cout << "~Building(): "
		 << "Destroying building." << endl;
}

