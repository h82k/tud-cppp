#include "Floor.hpp"

int getNumPeople() {
	return containedPeople.size();
}

Person getPerson(int i) {
	return containedPeople.at(i);
}

void Floor::addWaitingPerson(Person h) {
	containedPeople.push_back(h);
}

std::vector<Person> Floor::removeAllPeople() {
	std::vector<Person> people = containedPeople;
	containedPeople.clear();
	return people;
}
