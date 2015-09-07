#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
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
	inline int getNumberOfFLoors() const {
		return floors.size();
	}

	/** get a certain floor */
	const Floor& getFloor(int floor) const;

	/** get the elevator of this building */
	inline const Elevator& getElevator() const {
		return elevator;
	}

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

private:
	/** Floors of this building */
	std::list<Floor> floors;

	/** the Elevator */
	Elevator elevator;

	/** returns the floor with the given number. This non-const variant of the getter is
	 * for 'private' purposes only. */
	Floor& getFloor(int floor);
};

#endif /* BUILDING_HPP_ */
