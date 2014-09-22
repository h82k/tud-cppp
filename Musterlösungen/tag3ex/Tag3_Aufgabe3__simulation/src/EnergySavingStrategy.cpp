/*
 * EnergySavingStrategy.cpp
 */

#include "EnergySavingStrategy.hpp"
#include "Simulation.hpp"

#include <limits>
#include <cmath>

using namespace std;

EnergySavingStrategy::~EnergySavingStrategy() {
}

void EnergySavingStrategy::createPlan(const Building* building) {
	ElevatorStrategy::createPlan(building);
	
	std::list<int> tmpPlan;
	int maxEn = std::numeric_limits<int>::max();
	backtrack(*building, tmpPlan, maxEn);
}

int EnergySavingStrategy::nextFloor() {
	int f = plan.front();
	plan.pop_front();
	return f;
}

std::list<int> EnergySavingStrategy::getPotentiaNextlFloors(const Building& currentBuilding) {
	std::list<int> floors;
	
	// check all persons in elevator
	for (std::list<PersonPtr>::const_iterator citer = currentBuilding.getElevator().getContainedPeople().begin();
	        citer != currentBuilding.getElevator().getContainedPeople().end(); ++citer)
		floors.push_back((*citer)->getDestinationFloor());
	
	// check all floors
	for (int i = 0; i < currentBuilding.getNumberOfFLoors(); i++)
		if (currentBuilding.getFloor(i).getContainedPeople().size() > 0)
			floors.push_back(i);
	
	// remove duplicates
	floors.sort();
	floors.unique();
	return floors;
}

void EnergySavingStrategy::backtrack(const Building& currentBuilding, std::list<int>& tmpPlan, int& maxEnergy) {
	// explore possible movements
	std::list<int> floors = getPotentiaNextlFloors(currentBuilding);
	if (floors.empty()) { // no movements possible since we are done
		// so check if this is a plan with minimal energy
		if (currentBuilding.getElevator().getEnergyConsumed() < maxEnergy) {
			plan = tmpPlan;
			maxEnergy = currentBuilding.getElevator().getEnergyConsumed();
		}
	} else // otherwise try each movement
		for (std::list<int>::iterator iter = floors.begin(); iter != floors.end(); ++iter) {
			Building b(currentBuilding);
			
			// try current movement on building copy
			b.moveElevatorToFloor(*iter);
			b.removeArrivedPeople();
			b.letPeopleIn();
			
			// abort if energy is too high already
			if (b.getElevator().getEnergyConsumed() > maxEnergy) // don't check
				return;
			
			// save this move and try next branch
			tmpPlan.push_back(*iter);
			backtrack(b, tmpPlan, maxEnergy);
			tmpPlan.pop_back();
		}
	
	return;
}

