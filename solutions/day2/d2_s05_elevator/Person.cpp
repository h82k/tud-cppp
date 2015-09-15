#include "Person.hpp"
#include <iostream>

Person::Person(int destinationFloor):
	destinationFloor(destinationFloor)
{
	std::cout << "Creating Person with destination " << destinationFloor << std::endl;
}

Person::~Person() {
	std::cout << "Deleting Person with destination " << destinationFloor << std::endl;
}

int Person::getDestinationFloor() const {
	return destinationFloor;
}
