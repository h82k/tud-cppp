/*
 * Floor.cpp
 */

#include "Floor.hpp"

void Floor::addWaitingPerson(Person h) {
	containedPeople.push_back(h);
}

std::vector<Person> Floor::removeAllPeople() {
	std::vector<Person> people = containedPeople;
	containedPeople.clear();
	return people;
}
