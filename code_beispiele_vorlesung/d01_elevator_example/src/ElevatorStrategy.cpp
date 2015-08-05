/*
 * ElevatorStrategy.cpp
 *
 *  Created on: 15.07.2013
 *      Author: anjorin
 */

#include "ElevatorStrategy.h"
#include "Elevator.h"

using namespace std;

ElevatorStrategy::ElevatorStrategy() {
	cout << "ElevatorStrategy(): "
		 << "Creating basic strategy"
		 << endl;
}

ElevatorStrategy::~ElevatorStrategy() {
	cout << "~ElevatorStrategy(): "
		 << "Destroying basic strategy"
		 << endl;
}

const Floor* ElevatorStrategy::next(const Elevator* elevator) const{
	cout << "ElevatorStrategy::next(...): "
		 << "Using basic strategy ..."
		 << endl;
	return elevator->getCurrentFloor();
}


