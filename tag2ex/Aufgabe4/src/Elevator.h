/*
 * Elevator.h
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <list>

#include "Person.h"

/**
 * Represents an Elevator which can contain people and move to a floor.
 */
class Elevator {
public:
	/**
	 * Create an empty Elevator.
	 */
	Elevator();

	/** get number of floor the elevator is currently at. */
	inline int getFloor() {
		return currentFloor;
	}
	
	/** get consumed energy */
	inline double getEngergyConsumed() {
		return consumedEnergy;
	}
	
	/** Moves the elevator to given floor */
	void moveToFloor(int floor);
	
	/** get a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const {
		return containedPeople;
	}

	/** get number of people in Elevator */
	inline int getNumPeople() {
		return containedPeople.size();
	}
	
	/** add people to Elevator */
	void addPeople(std::list<PersonPtr> people);

	/** remove people which arrived at their destination */
	std::list<PersonPtr> removeArrivedPeople();

private:
	int currentFloor;
	std::list<PersonPtr> containedPeople;

	double consumedEnergy;
};

#endif /* ELEVATOR_H_ */
