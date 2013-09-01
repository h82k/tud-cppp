/*
 * Floor.cpp
 *
 */

#include "Floor.h"

Floor::Floor() {
	
}

void Floor::addWaitingHuman(PersonPtr h) {
	containedPeople.push_back(h);
}

std::list<PersonPtr> Floor::removeAllPeople() {
	std::list<PersonPtr> people = containedPeople;
	containedPeople.clear();
	return people;
}