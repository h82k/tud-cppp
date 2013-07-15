/*
 * Floor.cpp
 *
 *  Created on: 04.07.2013
 *      Author: anjorin
 */

#include <iostream>
using std::cout;
using std::endl;

#include "Floor.h"

Floor::Floor(int number):
		number(number) {
	cout << "Creating floor ["
		 << number
		 << "]" << endl;
}

Floor::Floor(const Floor& floor):
			number(floor.number+1) {
	cout << "Copying floor ["
		 << floor.number
		 << "]" << endl;
}

Floor::~Floor() {
	cout << "Destroying floor ["
		 << number
		 << "]" << endl;
}
