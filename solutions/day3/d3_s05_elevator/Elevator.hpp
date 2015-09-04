#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <list>
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
	inline int getFloor() const {
		return currentFloor;
	}
	
	/** get consumed energy */
	inline double getEnergyConsumed() const {
		return energyConsumed;
	}
	
	/** Moves the elevator to given floor */
	void moveToFloor(int floor);
	
	/** get a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const {
		return containedPeople;
	}
	
	/** get number of people in Elevator */
	inline int getNumPeople() const {
		return containedPeople.size();
	}
	
	/** add people to Elevator */
	void addPeople(const std::list<PersonPtr>& people);
	
	/** remove people which arrived at their destination */
	std::list<PersonPtr> removeArrivedPeople();
	
private:
	int currentFloor;
	std::list<PersonPtr> containedPeople;
	double energyConsumed;
};

#endif /* ELEVATOR_HPP_ */
