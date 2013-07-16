/*
 * Floor.cpp
 *
 *  Created on: 04.07.2013
 *      Author: anjorin
 */

#include <iostream>
using namespace std;

#include "Floor.h"

Floor::Floor(int number):
		number(number) {
	cout << "Floor(): "
		 << "Creating floor ["
		 << number
		 << "]" << endl;
}

Floor::Floor(const Floor& floor):
			number(floor.number) {
	cout << "Floor(const Floor&): "
		 << "Copying floor ["
		 << floor.number
		 << "]" << endl;
}

Floor::~Floor() {
	cout << "~Floor(): "
		 << "Destroying floor ["
		 << number
		 << "]" << endl;
}
