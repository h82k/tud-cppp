/*
 * SimpleElevatorStrategy.cpp
 *
 *  Created on: May 20, 2013
 *      Author: jgdo
 */

#include <set>
#include <stdexcept>
#include <exception>

#include "SimpleElevatorStrategy.h"
#include "Building.h"

SimpleElevatorStrategy::SimpleElevatorStrategy() {
}

SimpleElevatorStrategy::~SimpleElevatorStrategy() {
}

void SimpleElevatorStrategy::createPlan(const Building& building) {
	floorList.clear();
	
	std::set<int> destinations;
	
	int n = building.getNumberOfFLoors();
	for (int i = 0; i < n; i++) {
		const Floor& f = building.getFloor(i);
		if (f.hasPeopleWaiting()) {
			floorList.push_back(i);
			std::set<int> fd = f.getDestinationFloors();
			destinations.insert(fd.begin(), fd.end());
		}
	}
	
	floorList.insert(floorList.end(), destinations.begin(), destinations.end());
}

int SimpleElevatorStrategy::nextFloor() {
	if(floorList.empty())
		throw std::runtime_error("No next floor available!");
	
	int f = floorList.front();
	floorList.pop_front();
	return f;
}

