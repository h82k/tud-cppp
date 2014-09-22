/*
 * ElevatorStrategy.hpp
 */

#ifndef ELEVATORSTRATEGY_HPP_
#define ELEVATORSTRATEGY_HPP_

#include "Building.hpp"

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
	virtual void createPlan(const Building*);

	/** 
	 * get next floor to visit.
	 */
	virtual int nextFloor() = 0;

protected:
	/** Pointer to current building, set by createPlan() */
	const Building* building;
};

#endif /* ELEVATORSTRATEGY_HPP_ */
