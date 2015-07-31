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
	inline int getNumOfFloors() {
		return floors.size();
	}
	
	/** get a certain floor */
	inline Floor& getFloor(int floor) {
		return floors.at(floor);
	}
	
	/** get the elevator */
	inline Elevator& getElevator() {
		return elevator;
	}
	
	/** 
	 * Let people on current floor go into the elevator.
	 */
	void letPeopleIn();
	
	/** remove people from elevator on current floor which arrived at their destination */
	std::vector<Person> removeArrivedPeople();
	
	/** moves the building's elevator to given floor */
	void moveElevatorToFloor(int i);
	
	/** Add a person to given floor */
	void addWaitingPerson(int floor, Person p);
	
private:
	/** Floors of this building */
	std::vector<Floor> floors;
	
	/** the Elevator */
	Elevator elevator;
};

#endif /* BUILDING_HPP_ */
