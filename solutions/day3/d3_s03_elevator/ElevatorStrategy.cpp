#include "ElevatorStrategy.hpp"

ElevatorStrategy::~ElevatorStrategy() {}

void ElevatorStrategy::createPlan(const Building *b) {
	building = b;
}

