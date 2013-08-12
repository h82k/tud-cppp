/*
 * Floor.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include "Floor.h"

Floor::Floor() {
	
}

void Floor::addWaitingHuman(Person h) {
	containedPeople_.push_back(h);
}

std::vector<Person> Floor::removeAllPeople() {
	std::vector<Person> people = containedPeople_;
	containedPeople_.clear();
	return people;
}
