/*
 * Building.h
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <vector>

#include "Floor.h"
#include "Elevator.h"

/**
 * Represents a Building with floors and an Elevator
 */
class Building {
public:
	/**
	 * Create a Building with given number of floors.
	 */
	Building(int numberOfFloors);

	/** get number of floors */
	inline int getNumOfFloors() {
		return floors.size();
	}
	
	/** get a certain floor */
	inline Floor& getFloor(int floor) {
		return floors.at(floor);
	}
	
	/** get the elevator */
	inline Elevator& getElevator() {
		return elevator;
	}
	
private:
	/** Floors of this building */
	std::vector<Floor> floors;

	/** the Elevator */
	Elevator elevator;
};

#endif /* BUILDING_H_ */
