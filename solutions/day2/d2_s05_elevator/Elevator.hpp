#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <list>
#include "Person.hpp"		// required for PersonPtr

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
	int getFloor() const;
	
	/** get consumed energy */
	double getEnergyConsumed() const;
	
	/** Moves the elevator to given floor */
	void moveToFloor(int floor);
	
	/** get a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const;
	
	/** get number of people in Elevator */
	int getNumPeople() const;
	
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
