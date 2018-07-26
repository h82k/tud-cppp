#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <vector>
#include "Floor.hpp"
#include "Elevator.hpp"

/**
 * @name Building
 * @author cppp
 * @brief class to describe a building with floors and an elevator
 */
class Building {
public:
    /**
     * @name Building(int numberOfFloors);
     * @author cppp
     * @brief creator of building object with a given number of floors
     * @param numberOfFloors the number of floors
     */
	Building(int numberOfFloors);				// create a Building with given number of floors
    /**
     * @name getNumOfFloors() const;
     * @author cppp
     * @brief returns the number of floors
     * @return this->floors.size();
     */
	int getNumberOfFloors() const;				// get number of floors
    /**
     * @name getFloor(int floor) const;
     * @author cppp
     * @brief returns a floor by a given number as const reference
     * @param floor number of floor to return
     * @return this->floors[floor] as reference
     */
	const Floor& getFloor(int floor) const;		// get a certain floor
    /**
     * @name getElevator() const;
     * @author cppp
     * @brief returns a reference of the building's elevator
     * @return elevator reference
     */
	const Elevator& getElevator() const;		// get the elevator (constant reference)
	
    /**
     * @name letPeopleIn();
     * @author cppp
     * @brief moves waiting people of the floor the elevator is currently in into the elevator
     */
	void letPeopleIn();								// let people on current floor into elevator
    /**
     * @name removeArrivedPeople();
     * @author cppp
     * @brief removes arrived people out of the elevator
     * @return a vector of the arrived people
     */
	std::list<PersonPtr> removeArrivedPeople();		// move the elevator to a given floor
    /**
     * @name moveElevatorToFloor(int i);
     * @author cppp
     * @brief move the elevator to the i-th floor
     * @param i the floor number the elevator moves to
     */
	void moveElevatorToFloor(int i);				// add a person to a given floor
    /**
     * @name addWaitingPerson(int floor, Person p);
     * @author cppp
     * @brief add waiting person p to the floor-th floor
     * @param floor the number of the floor
     * @param p the person to add
     */
	void addWaitingPerson(int floor, PersonPtr p);	// remove people which arrived at their destination from the elevator on the current floor
private:
	std::list<Floor> floors;				// floors of this building
	Elevator elevator;						// the elevator
	Floor& getFloor(int floor);				// get the elevator (non-constant reference)
};

#endif /* BUILDING_HPP_ */
