/*
 * Elevator.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <vector>

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

	/** Returns number of people in Elevator */
	inline int getNumPeople() {
		return containedPeople_.size();
	}
	
	/** returns i-th human in Elevator */
	inline Person getHuman(int i) {
		return containedPeople_.at(i);
	}
	
	/** add people to Elevator */
	void addPeople(std::vector<Person> people);

	/** remove people which arrived at their destination */
	std::vector<Person> removeArrivedPeople();

private:
	int currentFloor_;
	std::vector<Person> containedPeople_;

	double usedEnergy;
};

#endif /* ELEVATOR_H_ */
