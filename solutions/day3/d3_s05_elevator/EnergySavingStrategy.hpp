#ifndef ENERGYSAVINGSTRATEGY_HPP_
#define ENERGYSAVINGSTRATEGY_HPP_

#include "ElevatorStrategy.hpp"
#include <list>

//Finds a strategy for minimizing the energy by performing backtracking
class EnergySavingStrategy: public ElevatorStrategy {
public:
	virtual ~EnergySavingStrategy();
	virtual void createPlan(const Building*);
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
