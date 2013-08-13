/*
 * Human.cpp
 */

#include "Person.h"

#include <iostream>
using namespace std;

Person::Person(int destinationFloor) :
		destinationFloor(destinationFloor) {
	cout << "Creating Human with destination " << destinationFloor << endl;
}

Person::~Person() {
	cout << "Deleting Human with destination " << destinationFloor << endl;
}

