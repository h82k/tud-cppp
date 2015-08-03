#include "Elevator.hpp"
#include <cmath>
#include <iostream>

Elevator::Elevator():
	currentFloor(0), energyConsumed(0)
{}

void Elevator::moveToFloor(int floor) {
	energyConsumed += std::abs(currentFloor - floor);
	currentFloor = floor;
	std::cout << "Moving to floor " << floor << std::endl;
}

void Elevator::addPeople(std::vector<Person> people) {
	containedPeople.insert(containedPeople.end(), people.begin(), people.end());
	std::cout << "Adding " << people.size() << " people" << std::endl;
}

std::vector<Person> Elevator::removeArrivedPeople() {
	std::vector<Person> stay; // list of people who stay in elevator
	std::vector<Person> arrived; // list of people who arrived at their destination
	
	// check for each person ...
	for(size_t i = 0; i < containedPeople.size(); ++i) {
		// whether it arrived
		if(containedPeople.at(i).getDestinationFloor() == getFloor()) {
			arrived.push_back(containedPeople.at(i));
		}
		else {
			stay.push_back(containedPeople.at(i));
		}
	}
	
	containedPeople = stay;
	std::cout << "Removing " << arrived.size() << " arrived people" << std::endl;
	return arrived;
}
