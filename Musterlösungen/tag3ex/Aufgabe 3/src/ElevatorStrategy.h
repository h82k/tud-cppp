/*
 * ElevatorStrategy.h
 */

#ifndef ELEVATORSTRATEGY_H_
#define ELEVATORSTRATEGY_H_

#include "Building.h"

/**
 * Elevator strategy base class. Used to determine at which floor the elevator should move next.
 */
class ElevatorStrategy {
public:
	virtual ~ElevatorStrategy();

	/**
	 * Creates a plan for the simulation. 
	 * Default implementation does nothing but saving the building pointer.
	 */
	virtual void createPlan(Building*);

	/** 
	 * get next floor to visit.
	 */
	virtual int nextFloor() = 0;

protected:
	/** Pointer to current building, set by createPlan() */
	Building* building;
};

#endif /* ELEVATORSTRATEGY_H_ */
