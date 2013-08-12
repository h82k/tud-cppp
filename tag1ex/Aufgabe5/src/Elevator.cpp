/*
 * Elevator.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include <stdlib.h> 
#include <iostream>

using namespace std;

#include "Elevator.h"

Elevator::Elevator() :
		currentFloor_(0), usedEnergy(0) {
}

void Elevator::moveToFloor(int floor) {
	usedEnergy += abs(currentFloor_ - floor);
	currentFloor_ = floor;
	
	cout << "Moving to floor " << floor << endl;
}

void Elevator::addPeople(std::vector<Person> people) {
	containedPeople_.insert(containedPeople_.end(), people.begin(), people.end());
	
	cout << "Adding " << people.size() << " people" << endl;
}

std::vector<Person> Elevator::removeArrivedPeople() {
	std::vector<Person> stay;
	std::vector<Person> arrived;
	
	for(int i = 0; i < containedPeople_.size(); i++) {
		if(containedPeople_.at(i).destinationFloor() == getFloor())
			arrived.push_back(containedPeople_.at(i));
		else
			stay.push_back(containedPeople_.at(i));
	}
	
	containedPeople_ = stay;
	
	cout << "Removing " << arrived.size() << " arrived people" << endl; 
	
	return arrived;
}
