/*
 * Simulation.cpp
 */

#include "Simulation.h"

#include <iostream>
#include <list>
using namespace std;

std::list<int> runSimulation(Building& building, ElevatorStrategy& strategy) {
	strategy.createPlan(&building);
	
	std::list<int> visitedFloors;
	
	 cout << "elevator at " << building.getElevator().getFloor() << endl;
	 cout << "creating plan" << endl;
	
	while (building.containsPeople()) {
		int nextFloor = strategy.nextFloor();
		cout << "moving to floor " << nextFloor << endl;
		
		visitedFloors.push_back(nextFloor);
		building.moveElevatorToFloor(nextFloor);
		
		int n = building.removeArrivedPeople().size();
		cout << "removing " << n << " arrived people" << endl;
		
		building.letPeopleIn();
		// cout << "letting people in" << endl;
	}

	 cout << "end" << endl;
	 cout << "energy consumed: " << building.getElevator().getEnergyConsumed() << endl;
	 cout << "floors visited: " << visitedFloors.size() << endl;
	
	return visitedFloors;
}
