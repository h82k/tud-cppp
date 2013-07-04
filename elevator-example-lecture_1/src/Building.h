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
	~Building();

	void runSimulation();

private:
	std::vector<Floor> floors;
	Elevator elevator;
};

#endif /* BUILDING_H_ */
