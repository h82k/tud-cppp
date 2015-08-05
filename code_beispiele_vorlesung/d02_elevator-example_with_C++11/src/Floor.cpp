/*
 * Floor.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include "Floor.h"

Floor::Floor() {
	
}

void Floor::addWaitingPeople(const std::list<HumanPtr>& people) {
	containedPeople_.insert(containedPeople_.end(), people.begin(), people.end());
}

std::list<HumanPtr> Floor::removeAllPeople() {
	std::list<HumanPtr> people = containedPeople_;
	containedPeople_.clear();
	return people;
}

std::set<int> Floor::getDestinationFloors() const {
	std::set<int> floors;
	
	for (std::list<HumanPtr>::const_iterator iter = containedPeople_.begin();
			iter != containedPeople_.end(); ++iter)
		floors.insert((*iter)->destinationFloor());
	
	return floors;
}
