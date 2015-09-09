/*
 * Simulation.cpp
 *
 *  Created on: May 20, 2013
 *      Author: jgdo
 */

#include <ctime>
#include <cstdlib>
#include <list>

#include "Human.h"
#include "Building.h"
#include "SimpleElevatorStrategy.h"

const std::list<HumanPtr> createPeopleList(int n) {
	static std::list<HumanPtr> people;
	
	people.clear();
	while(n-- > 0)
		people.push_back(HumanPtr(new Human(std::rand() % 10)));
	
	return people;
}

int main(int argc, char **argv) {
	SimpleElevatorStrategy strategy;
	Building building(10, &strategy);
	
	building.addPeopleToFloor(2, createPeopleList(5));
	building.addPeopleToFloor(3, createPeopleList(5));
	building.addPeopleToFloor(7, createPeopleList(5));
	
	building.runSimulation();
}
