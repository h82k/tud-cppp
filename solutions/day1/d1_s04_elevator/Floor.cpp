#include "Floor.hpp"

int Floor::getNumPeople() {
	return containedPeople.size();
}

Person Floor::getPerson(int i) {
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
