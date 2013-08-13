/*
 * Building.cpp
 *
 */

#include <iostream>

using std::cout;
using std::endl;

#include "Building.h"

Building::Building(int numberOfFloors) {
	// add given number of floors
	while (numberOfFloors-- > 0)
		floors.push_back(Floor());
}

