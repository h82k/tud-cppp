/*
 * Elevator.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <list>

#include "Human.h"

class Elevator {
public:
	Elevator();

	inline int getFloor() const {
		return currentFloor_;
	}
	
	inline int engergyConsumed() const {
		return engeryConsumed_;
	}
	
	void moveToFloor(int floor);

	void addPeople(const std::list<HumanPtr>& people);
	std::list<HumanPtr> removeArrivedPeople();

private:
	int currentFloor_;
	std::list<HumanPtr> containedPeople_;

	int engeryConsumed_;
};

#endif /* ELEVATOR_H_ */
