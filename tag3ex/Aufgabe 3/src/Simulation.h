/*
 * Simulation.h
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

class Simulation {
public:
	Simulation(Building& building);
	
	void runSimulation();
	
private:
	Building& building;
};

#endif /* SIMULATION_H_ */
