#include "Building.hpp"

Building::Building(int numberOfFloors) {
	// add given number of floors
	while (numberOfFloors-- > 0) {
		floors.push_back(Floor());
	}
}

const Floor& Building::getFloor(int floor) const {
	std::list<Floor>::const_iterator iter = floors.begin();

	for (int i = 0; i < floor; ++i) {
		++iter;
	}
	return *iter;
}

Floor& Building::getFloor(int floor) {
	std::list<Floor>::iterator iter = floors.begin();

	for (int i = 0; i < floor; ++i) {
		++iter;
	}
	return *iter;
}

void Building::letPeopleIn() {
	elevator.addPeople(getFloor(elevator.getFloor()).removeAllPeople());
}

std::list<PersonPtr> Building::removeArrivedPeople() {
	return elevator.removeArrivedPeople();
}

void Building::moveElevatorToFloor(int i) {
	elevator.moveToFloor(i);
}

void Building::addWaitingPerson(int floor, PersonPtr p) {
	getFloor(floor).addWaitingPerson(p);
}

