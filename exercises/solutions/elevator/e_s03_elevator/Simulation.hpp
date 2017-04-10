#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include "ElevatorStrategy.hpp"
#include <list>

/** Runs an elevator simulation on given building with given strategy */
std::list<int> runSimulation(Building& building, ElevatorStrategy& strategy);

#endif /* SIMULATION_HPP_ */
