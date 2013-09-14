/*
 * Simulation.cpp
 */

#include "Simulation.h"

#include <iostream>
using namespace std;

std::list<int> runSimulation(Building& building, ElevatorStrategy& strategy) {
	strategy.createPlan(&building);
	
	std::list<int> visitedFloors;
	
	// cout << "elevator at " << building.getElevator().getFloor() << endl;
	// cout << "creating plan" << endl;
	
	while (building.containsPeople()) {
		int nextFloor = strategy.nextFloor();
		// cout << "moving to floor " << nextFloor << endl;
		
		visitedFloors.push_back(nextFloor);
		building.getElevator().moveToFloor(nextFloor);
		
		int n = building.getElevator().removeArrivedPeople().size();
		// cout << "removing " << n << " arrived people" << endl;
		
		Floor& f = building.getFloor(building.getElevator().getFloor());
		// cout << "letting " << f.getContainedPeople().size() << " people in" << endl;
		building.getElevator().addPeople(f.removeAllPeople());
	}

	// cout << "end" << endl;
	// cout << "energy consumed: " << building.getElevator().getEnergyConsumed() << endl;
	// cout << "floors visited: " << visitedFloors.size() << endl;
	
	return visitedFloors;
}
