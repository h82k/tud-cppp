/*
 * ElevatorStrategy.h
 */

#ifndef ELEVATORSTRATEGY_H_
#define ELEVATORSTRATEGY_H_

#include "Building.h"

class ElevatorStrategy {
public:
	virtual ~ElevatorStrategy();
	
	
	virtual void createPlan(Building&);
	virtual int compteNextFloor(Building&) = 0;
};

#endif /* ELEVATORSTRATEGY_H_ */
