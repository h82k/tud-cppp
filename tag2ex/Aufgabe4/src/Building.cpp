/*
 * Building.cpp
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#include <iostream>

using std::cout;
using std::endl;

#include "Building.h"

Building::Building(int numberOfFloors) {
	while (numberOfFloors-- > 0)
		floors_.push_back(Floor());
}

