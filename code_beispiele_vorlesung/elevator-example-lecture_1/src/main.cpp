//====================================
// Name: elevator-example-lecture.cpp
//====================================

#include <iostream>
using namespace std;

#include "Building.h"
#include "ElevatorStrategy.h"
#include "EnergyMinimizingStrategy.h"

int main() {
	ElevatorStrategy* strg = new EnergyMinimizingStrategy();

	// Do something...

	ConstElevatorStrategyPtr strategy(strg);
	Building hbi(6, strategy);

	hbi.getElevator().moveToNextFloor();
}

