/*
 * Human.cpp
 */

#include "Person.h"

#include <iostream>
using namespace std;

Person::Person(int destinationFloor) :
		destinationFloor(destinationFloor) {
	cout << "Creating Person with destination " << destinationFloor << endl;
}

Person::Person(const Person& other) :
		destinationFloor(other.destinationFloor) {
	cout << "Copying person with destination " << destinationFloor << endl;
}

Person::~Person() {
	cout << "Deleting Person with destination " << destinationFloor << endl;
}

