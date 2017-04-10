#include "Building.hpp"

int Building::getNumOfFloors() {
	return floors.size();
}

Floor& Building::getFloor(int floor) {
	return floors.at(floor);
}

Elevator& Building::getElevator() {
	return elevator;
}

Building::Building(int numberOfFloors) {
	// add given number of floors
	for(int i = 0; i < numberOfFloors; ++i) {
		floors.push_back(Floor());
	}
}

void Building::letPeopleIn() {
	int floor = elevator.getFloor();
	std::vector<Person> people = floors.at(floor).removeAllPeople();
	elevator.addPeople(people);
}

std::vector<Person> Building::removeArrivedPeople() {
	return elevator.removeArrivedPeople();
}

void Building::moveElevatorToFloor(int i) {
	elevator.moveToFloor(i);
}

void Building::addWaitingPerson(int floor, Person p) {
	floors.at(floor).addWaitingPerson(p);
}
