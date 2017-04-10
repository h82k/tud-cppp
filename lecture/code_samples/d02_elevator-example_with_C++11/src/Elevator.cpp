/*
 * Elevator.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include <cmath>

#include "Elevator.h"

Elevator::Elevator() :
		currentFloor_(0), engeryConsumed_(0) {
}

void Elevator::moveToFloor(int floor) {
	engeryConsumed_ += std::abs(currentFloor_ - floor);
	currentFloor_ = floor;
}

void Elevator::addPeople(const std::list<HumanPtr>& people) {
	containedPeople_.insert(containedPeople_.end(), people.begin(), people.end());
}

std::list<HumanPtr> Elevator::removeArrivedPeople() {
	std::list<HumanPtr>::iterator iter = containedPeople_.begin();
	
	std::list<HumanPtr> quit;
	
	while (iter != containedPeople_.end()) {
		if ((*iter)->destinationFloor() == getFloor()) {
			quit.push_back(*iter);
			iter = containedPeople_.erase(iter);
		} else
			++iter;
	}
	
	return quit;
}
