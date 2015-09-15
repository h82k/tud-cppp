#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <list>
#include <vector>
#include "Person.hpp"
#include "Floor.hpp"
#include "Elevator.hpp"

/**
 * Represents a Building with floors and an Elevator
 */
class Building {
public:
	/**
	 * Create a Building with given number of floors.
	 */
	Building(int numberOfFloors);
	
	/** get number of floors */
	int getNumberOfFLoors() const;
	
	/** get a certain floor */
	const Floor& getFloor(int floor) const;
	
	/** get the elevator of this building */
	const Elevator& getElevator() const;
	
	/** 
	 * Let people on current floor go into the elevator.
	 */
	void letPeopleIn();
	
	/** remove people from elevator on current floor which arrived at their destination */
	std::list<PersonPtr> removeArrivedPeople();
	
	/** moves the building's elevator to given floor */
	void moveElevatorToFloor(int i);
	
	/** Add a person to given floor */
	void addWaitingPerson(int floor, PersonPtr p);
	
	/** true if some people are in the building (on floors or in elevator) */
	bool containsPeople() const;
private:
	/** Floors of this building */
	std::vector<Floor> floors;
	
	/** the Elevator */
	Elevator elevator;
};

#endif /* BUILDING_HPP_ */
