/*
 * EnergyMinimizingStrategy.cpp
 *
 *  Created on: 15.07.2013
 *      Author: anjorin
 */

#include <iostream>

#include "EnergyMinimizingStrategy.h"
#include "Elevator.h"
using namespace std;

EnergyMinimizingStrategy::EnergyMinimizingStrategy() : ElevatorStrategy(){
	cout << "EnergyMinimizingStrategy(): "
		 << "Creating energy minimizing strategy" << endl;
}

EnergyMinimizingStrategy::~EnergyMinimizingStrategy() {
	cout << "~EnergyMinimizingStrategy(): "
		 << "Destroying energy minimizing strategy" << endl;
}

const Floor* EnergyMinimizingStrategy::next(const Elevator* elevator) const {
	cout << "EnergyMinimizingStrategy::next(...): "
		 << "Perform some complex calculation ..." << endl;

	return elevator->getCurrentFloor();
}

