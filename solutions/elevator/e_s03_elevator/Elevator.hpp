#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <list>
#include "Person.hpp"

class Elevator {
public:
	Elevator();							// create an elevator at floor 0, no people inside and 0 energy consumed
	int getFloor() const;				// get number of floor the elevator is currently at
	double getEnergyConsumed() const;	// get consumed energy
	void moveToFloor(int floor);		// move the elevator to given floor (consumes energy)
	const std::list<PersonPtr>& getContainedPeople() const;
	int getNumPeople() const;								// get number of people in Elevator
	void addPeople(const std::list<PersonPtr>& people);		// add people to Elevator
	std::list<PersonPtr> removeArrivedPeople();				// remove people which arrived
private:
	int currentFloor;								// current floor number
	std::list<PersonPtr> containedPeople;			// people currently in elevator
	double energyConsumed;							// energy consumed
};

#endif /* ELEVATOR_HPP_ */
