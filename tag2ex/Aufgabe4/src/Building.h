/*
 * Building.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <vector>

#include "Floor.h"
#include "Elevator.h"

class Building {
public:
	Building(int numberOfFloors);

	/** return number of floors */
	inline int getNumberOfFLoors() {
		return floors_.size();
	}
	
	/** return a certain floor */
	inline Floor& getFloor(int floor) {
		return floors_.at(floor);
	}

	inline Elevator& getElevator() {
		return elevator_;
	}
	
private:
	std::vector<Floor> floors_;
	Elevator elevator_;
};

#endif /* BUILDING_H_ */
