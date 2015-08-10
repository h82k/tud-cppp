/*
 * ElevatorStrategy.h
 *
 *  Created on: 15.07.2013
 *      Author: anjorin
 */

#ifndef ELEVATORSTRATEGY_H_
#define ELEVATORSTRATEGY_H_

#include "Floor.h"

class Elevator;

class ElevatorStrategy {
public:
	ElevatorStrategy();
	virtual ~ElevatorStrategy();

	virtual const Floor* next(const Elevator* elevator) const = 0;
};

#endif /* ELEVATORSTRATEGY_H_ */
