/*
 * Floor.cpp
 *
 */

#include "Floor.hpp"

Floor::Floor() {
	
}

void Floor::addWaitingPerson(PersonPtr h) {
	containedPeople.push_back(h);
}

std::list<PersonPtr> Floor::removeAllPeople() {
	std::list<PersonPtr> people = containedPeople;
	containedPeople.clear();
	return people;
}
