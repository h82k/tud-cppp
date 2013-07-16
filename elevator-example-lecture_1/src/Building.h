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
	Building(int numberOfFloors, ConstElevatorStrategyPtr strategy);
	~Building();

	inline int numberOfFloors() const {
		return floors.size();
	}

	inline Elevator& getElevator() {
		return elevator;
	}

private:
	std::vector<Floor> floors;
	Elevator elevator;
};

#endif /* BUILDING_H_ */
