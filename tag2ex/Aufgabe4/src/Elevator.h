/*
 * Elevator.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <list>

#include "Person.h"

class Elevator {
public:
	Elevator();

	inline int getFloor() {
		return currentFloor_;
	}
	
	inline double engergyConsumed() {
		return usedEnergy;
	}
	
	/** Moves the elevator to given floor */
	void moveToFloor(int floor);
	
	/** return a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const {
		return containedPeople;
	}

	/** Returns number of people in Elevator */
	inline int getNumPeople() {
		return containedPeople.size();
	}
	
	/** add people to Elevator */
	void addPeople(std::list<PersonPtr> people);

	/** remove people which arrived at their destination */
	std::list<PersonPtr> removeArrivedPeople();

private:
	int currentFloor_;
	std::list<PersonPtr> containedPeople;

	double usedEnergy;
};

#endif /* ELEVATOR_H_ */
