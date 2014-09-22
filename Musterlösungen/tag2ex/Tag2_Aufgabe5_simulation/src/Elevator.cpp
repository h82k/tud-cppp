/*
 * Elevator.cpp
 */

#include <cstdlib> 
#include <iostream>

using namespace std;

#include "Elevator.hpp"

Elevator::Elevator() :
		currentFloor(0), energyConsumed(0) {
}

void Elevator::moveToFloor(int floor) {
	energyConsumed += abs(currentFloor - floor);
	currentFloor = floor;
	
	cout << "Moving to floor " << floor << endl;
}

void Elevator::addPeople(const std::list<PersonPtr>& people) {
	containedPeople.insert(containedPeople.end(), people.begin(), people.end());
	
	cout << "Adding " << people.size() << " people" << endl;
}

std::list<PersonPtr> Elevator::removeArrivedPeople() {
	std::list<PersonPtr> arrived;
	
	// create iterator for containedPeople
	std::list<PersonPtr>::iterator iter = containedPeople.begin();
	
	// iterate through all elements
	while (iter != containedPeople.end()) {
		PersonPtr person = *iter; // get person smart pointer at current position
		
		// check whether person has reached it's destination Floor
		if (person->getDestinationFloor() == getFloor()) {
			// erase person pointer from containedPeople
			// the erase method will return an iterator to the next item
			iter = containedPeople.erase(iter);
			// remember arrived person 
			arrived.push_back(person);
		} else
			++iter; // check next person
	}

	cout << "Removing " << arrived.size() << " arrived people" << endl;
	
	return arrived;
}
