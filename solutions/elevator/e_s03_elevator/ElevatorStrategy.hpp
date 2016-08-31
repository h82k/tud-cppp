#ifndef ELEVATORSTRATEGY_HPP_
#define ELEVATORSTRATEGY_HPP_

#include "Building.hpp"

/**
 * @name ElevatorStrategy
 * @author cppp
 * @brief elevator strategy class: determines to which floor the elevator should move next.
 */
class ElevatorStrategy {
public:
    /**
     * @name ~ElevatorStrategy();
     * @author cppp
     * @brief virtual destructor
     */
	virtual ~ElevatorStrategy();
    /**
     * @name createPlan(const Building*);
     * @author cppp
     * @brief create plan for simulation, default simply stores the given pointer
     * @param Building* building pointer
     */
	virtual void createPlan(const Building*);	// create a plan for the simulation - the default implementation does nothing but saving the building pointer
    /**
     * @name nextFloor() = 0;
     * @author cppp
     * @brief pure virtual method to calculate the next floor
     */
	virtual int nextFloor() = 0;				// get the next floor to visit
protected:
	const Building* building;					// pointer to current building, set by createPlan()
};

#endif /* ELEVATORSTRATEGY_HPP_ */
