/*
 * Elevator.cpp
 */

#include <stdlib.h> 
#include <iostream>

using namespace std;

#include "Elevator.h"

Elevator::Elevator() :
		currentFloor(0), consumedEnergy(0) {
}

void Elevator::moveToFloor(int floor) {
	consumedEnergy += abs(currentFloor - floor);
	currentFloor = floor;
	
	cout << "Moving to floor " << floor << endl;
}

void Elevator::addPeople(std::vector<Person> people) {
	containedPeople.insert(containedPeople.end(), people.begin(), people.end());
	
	cout << "Adding " << people.size() << " people" << endl;
}

std::vector<Person> Elevator::removeArrivedPeople() {
	std::vector<Person> stay; // list of people who stay in elevator
	std::vector<Person> arrived; // list of people who arrived at their destination
	
	// check for each person ...
	for(int i = 0; i < containedPeople.size(); i++) {
		// whether it arrived
		if(containedPeople.at(i).destinationFloor() == getFloor())
			arrived.push_back(containedPeople.at(i));
		else
			stay.push_back(containedPeople.at(i));
	}
	
	containedPeople = stay;
	
	cout << "Removing " << arrived.size() << " arrived people" << endl; 
	
	return arrived;
}
