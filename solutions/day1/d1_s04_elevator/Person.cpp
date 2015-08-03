#include "Person.hpp"
#include <iostream>

Person::Person(int destinationFloor):
	destinationFloor(destinationFloor)
{
	std::cout << "Creating Person with destination " << destinationFloor << std::endl;
}

Person::Person(const Person& other):
	destinationFloor(other.destinationFloor)
{
	std::cout << "Copying person with destination " << destinationFloor << std::endl;
}

Person::~Person() {
	std::cout << "Deleting Person with destination " << destinationFloor << std::endl;
}

