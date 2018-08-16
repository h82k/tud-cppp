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
#include "ElevatorStrategy.h"

class Building {
public:
	Building(int numberOfFloors, ElevatorStrategy* strategy);
	~Building();

	inline int getNumberOfFLoors() const {
		return floors_.size();
	}
	
	inline const Floor& getFloor(int floor) const {
		return floors_.at(floor);
	}
	
	void addPeopleToFloor(int floor, const std::list<HumanPtr>& people);
	
	void runSimulation();

private:
	std::vector<Floor> floors_;
	Elevator elevator_;
	int numPeople_;

	ElevatorStrategy* elevatorStrategy_;
};

#endif /* BUILDING_H_ */
