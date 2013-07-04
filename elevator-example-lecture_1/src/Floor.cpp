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

Floor::Floor() {
	cout << "Creating floor." << endl;
}

Floor::Floor(const Floor& floor){
	cout << "Copying floor." << endl;
}

Floor::~Floor() {
	cout << "Destroying floor." << endl;
}
