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
	cout << "Creating Human with destination " << destinationFloor << endl;
}

Person::~Person() {
	cout << "Deleting Human with destination " << destinationFloor_ << endl;
}

