#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "Floor.hpp"
#include "Elevator.hpp"

class Building {
public:
	Building(int numberOfFloors);	// create a Building with given number of floors
	int getNumberOfFLoors() const;				// get number of floors
	const Floor& getFloor(int floor) const;		// get a certain floor
	const Elevator& getElevator() const;		// get the elevator (constant reference)
	
	void letPeopleIn();								// let people on current floor into elevator
	std::list<PersonPtr> removeArrivedPeople();		// move the elevator to a given floor
	void moveElevatorToFloor(int i);				// add a person to a given floor
	void addWaitingPerson(int floor, PersonPtr p);	// remove people which arrived at their destination from the elevator on the current floor
private:
	std::list<Floor> floors;				// floors of this building
	Elevator elevator;						// the elevator
	Floor& getFloor(int floor);				// get the elevator (non-constant reference)
};

#endif /* BUILDING_HPP_ */
