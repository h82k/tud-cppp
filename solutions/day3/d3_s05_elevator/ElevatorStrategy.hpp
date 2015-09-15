#ifndef ELEVATORSTRATEGY_HPP_
#define ELEVATORSTRATEGY_HPP_

#include "Building.hpp"

// Elevator strategy class: Determines to which floor the elevator should move next.
class ElevatorStrategy {
public:
	virtual ~ElevatorStrategy();
	virtual void createPlan(const Building*);	// create a plan for the simulation - the default implementation does nothing but saving the building pointer
	virtual int nextFloor() = 0;				// get the next floor to visit
protected:
	const Building* building;					// pointer to current building, set by createPlan()
};

#endif /* ELEVATORSTRATEGY_HPP_ */
