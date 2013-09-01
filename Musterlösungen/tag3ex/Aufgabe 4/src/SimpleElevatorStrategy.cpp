/*
 * SimpleElevatorStrategy.cpp
 */

#include "SimpleElevatorStrategy.h"

SimpleElevatorStrategy::~SimpleElevatorStrategy() {
}

int SimpleElevatorStrategy::nextFloor() {
	if (building->getElevator().getContainedPeople().size() > 0)
		return building->getElevator().getContainedPeople().front()->getDestinationFloor();
	else {
		for (int i = 0; i < building->getNumberOfFLoors(); i++)
			if (building->getFloor(i).getContainedPeople().size() > 0)
				return i;
	}
	
	return 0;
}

