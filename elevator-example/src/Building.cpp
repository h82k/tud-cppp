/*
 * Building.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include <iostream>

using std::cout;
using std::endl;

#include "Building.h"

Building::Building(int numberOfFloors, ElevatorStrategy* strategy) :
		floors_(numberOfFloors, Floor()), numPeople_(0), elevatorStrategy_(strategy) {
}

Building::~Building() {
	// TODO: delete elevator strategy here?
}

void Building::addPeopleToFloor(int floor, const std::list<HumanPtr>& people) {
	floors_.at(floor).addWaitingPeople(people);
	numPeople_ += people.size();
}

void Building::runSimulation() {
	elevatorStrategy_->createPlan(*this);
	cout << "elevator at " << elevator_.getFloor() << endl;
	cout << "creating plan" << endl;
	
	while (numPeople_ > 0) {
		cout << "people left " << numPeople_ << endl;
		
		int nextFloor = elevatorStrategy_->nextFloor();
		cout << "moving to floor " << nextFloor << endl;
		elevator_.moveToFloor(nextFloor);
		
		int n = elevator_.removeArrivedPeople().size();
		cout << "people leaving elevator " << n << endl;
		numPeople_ -= n;
		
		Floor& f = floors_.at(elevator_.getFloor());
		cout << "people entering elevator " << f.getWaitingPeople().size() << endl;
		elevator_.addPeople(f.removeAllPeople());
	}
	
	cout << "end" << endl;
	cout << "energy consumed " << elevator_.engergyConsumed();
}

