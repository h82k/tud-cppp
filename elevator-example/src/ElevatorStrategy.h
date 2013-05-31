/*
 * ElevatorStrategy.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef ELEVATORSTRATEGY_H_
#define ELEVATORSTRATEGY_H_

#include <vector>

class Building;

class ElevatorStrategy {
public:
	virtual ~ElevatorStrategy();

	virtual void createPlan(const Building&) = 0;
	virtual int nextFloor() = 0;
};

#endif /* ELEVATORSTRATEGY_H_ */
