/*
 * Building.h
 *
 *  Created on: Aug 5, 2013
 *      Author: jgdo
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "Elevator.h"

class Building {
public:
	Building(int numberOfFloors);

	inline Elevator& getElevator() {
		return elevator;
	}
	
private:
	Elevator elevator;
};

#endif /* BUILDING_H_ */
