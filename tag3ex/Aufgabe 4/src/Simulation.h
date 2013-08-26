/*
 * Simulation.h
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "ElevatorStrategy.h"
#include <list>

/** Runs an elevator simulation on given building with given strategy */
std::list<int> runSimulation(Building& building, ElevatorStrategy& strategy);

#endif /* SIMULATION_H_ */
