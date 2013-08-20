/*
 * SimpleElevatorStrategy.h
 *
 *  Created on: May 20, 2013
 *      Author: jgdo
 */

#ifndef SIMPLEELEVATORSTRATEGY_H_
#define SIMPLEELEVATORSTRATEGY_H_

#include <list>

#include "ElevatorStrategy.h"

class SimpleElevatorStrategy: public ElevatorStrategy {
public:
	SimpleElevatorStrategy();
	virtual ~SimpleElevatorStrategy();
	
	virtual void createPlan(const Building&);
	virtual int nextFloor();
	
private:
	std::list<int> floorList;
};

#endif /* SIMPLEELEVATORSTRATEGY_H_ */
