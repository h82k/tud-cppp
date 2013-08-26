/*
 * SimpleElevatorStrategy.h
 */

#ifndef SIMPLEELEVATORSTRATEGY_H_
#define SIMPLEELEVATORSTRATEGY_H_

#include "ElevatorStrategy.h"

class SimpleElevatorStrategy: public ElevatorStrategy {
public:
	virtual ~SimpleElevatorStrategy();
	
	virtual int nextFloor();
};

#endif /* SIMPLEELEVATORSTRATEGY_H_ */
