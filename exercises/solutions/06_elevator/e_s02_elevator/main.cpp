#include "Building.hpp"
#include <iostream>

int main() {
	Building b(3);
	b.addWaitingPerson(0, std::make_shared<Person>(2)); // person in floor 0 wants to floor 2
	b.addWaitingPerson(1, std::make_shared<Person>(0)); // person in floor 1 wants to floor 0
	b.addWaitingPerson(2, std::make_shared<Person>(0)); // person in floor 2 wants to floor 0
	        
	for (int f = 0; f < b.getNumberOfFLoors(); ++f) {
		b.moveElevatorToFloor(f);
		b.letPeopleIn();
		while (b.getElevator().getNumPeople() > 0) {
			b.moveElevatorToFloor(b.getElevator().getContainedPeople().front()->getDestinationFloor());
			b.removeArrivedPeople();
		}
	}
	
	std::cout << "Energy consumed: " << b.getElevator().getEnergyConsumed() << std::endl;
}
