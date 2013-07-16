/*
 * Elevator.cpp
 *
 *  Created on: 04.07.2013
 *      Author: anjorin
 */

#include <iostream>
using std::cout;
using std::endl;

#include "Elevator.h"

Elevator::Elevator(const Floor* currentFloor,
		           ConstElevatorStrategyPtr strategy):
	currentFloor(currentFloor), strategy(strategy) {
	cout  << "Elevator(): "
		  << "Creating elevator." << endl;
}

Elevator::~Elevator(){
	cout << "~Elevator(): "
		 << "Destroying elevator." << endl;
}

void Elevator::moveToNextFloor(){
	cout << "Elevator::moveToNextFloor(): "
		 << " Polymorphic call to strategy." << endl;

	currentFloor = strategy->next(this);
}

