/*
 * Elevator.h
 *
 *  Created on: Aug 5, 2013
 *      Author: jgdo
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

class Elevator {
public:
	Elevator();
	
	inline double getUsedEnergy() {
		return usedEnergy;
	}
	
	inline int getTraversedFloors() {
		return traversedFloors;
	}
	
private:
	double usedEnergy;
	int traversedFloors;
};

#endif /* ELEVATOR_H_ */
