/*
 * Human.cpp
 */

#include "Person.hpp"

#include <iostream>
using namespace std;

Person::Person(int destinationFloor) :
		destinationFloor(destinationFloor) {
	cout << "Creating Person with destination " << destinationFloor << endl;
}

Person::~Person() {
	cout << "Deleting Person with destination " << destinationFloor << endl;
}

