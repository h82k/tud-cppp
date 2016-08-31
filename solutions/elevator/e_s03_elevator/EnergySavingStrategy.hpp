#ifndef ENERGYSAVINGSTRATEGY_HPP_
#define ENERGYSAVINGSTRATEGY_HPP_

#include "ElevatorStrategy.hpp"
#include <list>

/**
 * @name ElevatorSavingStrategy
 * @author cppp
 * @brief finds a strategy for minimizing the energy by performing backtracking
 */
class EnergySavingStrategy: public ElevatorStrategy {
public:
    /**
     * @name ~EnergySavingStrategy();
     * @author cppp
     * @brief destructor
     */
	virtual ~EnergySavingStrategy();
    /**
     * @name createPlan(const Building*);
     * @author cppp
     * @brief creating a plan, what to do in the given building
     */
	virtual void createPlan(const Building*);
    /**
     * @name nextFloor();
     * @author cppp
     * @brief calculates the next floor
     * @return int the next floor
     */
	virtual int nextFloor();
private: 
	// get a list with potential floors to find next
	// (potential floors are floors which either contain people or are set as destination floor by people in elevator)
	std::list<int> getPotentiaNextlFloors(const Building& currentBuilding);
	/**
	 * backtrack a possible solution
	 * @param currentBuilding current configuration
	 * @param tmpPlan: list for floor targets performed before
	 * @param maxEnergy: current max energy (can be overwritten if better plan was found)
	 */
	void backtrack(const Building& currentBuilding, std::list<int>& tmpPlan, int& maxEngery);
	std::list<int> plan;		// current plan
};

#endif /* ENERGYSAVINGSTRATEGY_HPP_ */
