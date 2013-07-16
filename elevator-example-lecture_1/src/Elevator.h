/*
 * Elevator.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "ElevatorStrategy.h"
#include "Floor.h"

class Elevator {
public:
	Elevator(const Floor*, ConstElevatorStrategyPtr);
	~Elevator();

	inline const Floor* getCurrentFloor() const{
		return currentFloor;
	}

	void moveToNextFloor();

private:
	const Floor* currentFloor;
	ConstElevatorStrategyPtr strategy;
};

#endif /* ELEVATOR_H_ */
