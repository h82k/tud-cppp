#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <vector>
#include "Person.hpp"

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
	inline double getEnergyConsumed() {
		return energyConsumed;
	}
	
	/** Moves the elevator to given floor */
	void moveToFloor(int floor);
	
	/** Returns number of people in Elevator */
	inline int getNumPeople() {
		return containedPeople.size();
	}
	
	/** returns i-th person in Elevator */
	inline Person getPerson(int i) {
		return containedPeople.at(i);
	}
	
	/** add people to Elevator */
	void addPeople(std::vector<Person> people);
	
	/** remove people which arrived at their destination */
	std::vector<Person> removeArrivedPeople();
private:
	/** current floor number */
	int currentFloor;
	
	/** people in elevator */
	std::vector<Person> containedPeople;
	
	/** energy consumed */
	double energyConsumed;
};

#endif /* ELEVATOR_HPP_ */
