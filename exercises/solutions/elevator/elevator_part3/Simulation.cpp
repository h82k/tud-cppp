#include "Simulation.hpp"
#include <iostream>

std::list<int> runSimulation(Building& building, ElevatorStrategy& strategy) {
	strategy.createPlan(&building);
	std::list<int> visitedFloors;
	std::cout << "elevator at " << building.getElevator().getFloor() << std::endl;
	std::cout << "creating plan" << std::endl;
	
	while (building.containsPeople()) {
		int nextFloor = strategy.nextFloor();
		std::cout << "moving to floor " << nextFloor << std::endl;
		visitedFloors.push_back(nextFloor);
		building.moveElevatorToFloor(nextFloor);
		int n = building.removeArrivedPeople().size();
		std::cout << "removing " << n << " arrived people" << std::endl;
		building.letPeopleIn();
		// std::cout << "letting people in" << std::endl;
	}
	std::cout << "end" << std::endl;
	std::cout << "energy consumed: " << building.getElevator().getEnergyConsumed() << std::endl;
	std::cout << "floors visited: " << visitedFloors.size() << std::endl;
	return visitedFloors;
}
