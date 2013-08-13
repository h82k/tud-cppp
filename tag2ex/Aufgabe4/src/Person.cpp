/*
 * Human.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include "Person.h"

#include <iostream>
using namespace std;

Person::Person(int destinationFloor) :
		destinationFloor_(destinationFloor) {
	cout << "Creating Person with destination " << destinationFloor << endl;
}

Person::~Person() {
	cout << "Deleting Person with destination " << destinationFloor_ << endl;
}

