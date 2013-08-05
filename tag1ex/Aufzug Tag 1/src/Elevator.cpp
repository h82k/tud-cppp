/*
 * Elevator.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: jgdo
 */
#include "Elevator.h"

#include <iostream>
using namespace std;


Elevator::Elevator() :
		usedEnergy(0), traversedFloors(0) {
	cout << "Creating Elevator" << endl;
}

