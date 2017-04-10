#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <list>
#include "Person.hpp"

/**
 * @name Elevator
 * @author cppp
 * @brief class describing an elevator
 */
class Elevator {
public:
    /**
     * @name Elevator();
     * @author cppp
     * @brief constructor of elevator object
     */
	Elevator();							// create an elevator at floor 0, no people inside and 0 energy consumed
    /**
     * @name getFloor() const;
     * @author cppp
     * @brief get number fo floor the elevator is currently at
     * @return int
     */
	int getFloor() const;				// get number of floor the elevator is currently at
    /**
     * @name getEnergyConsumed() const;
     * @author cppp
     * @brief returns the consumed energy since the creation
     * @return double
     */
	double getEnergyConsumed() const;	// get consumed energy
    /**
     * @name moveToFloor(int floor);
     * @author cppp
     * @brief move elevator to the given floor (consumes energy)
     * @param floor the floor number
     */
	void moveToFloor(int floor);		// move the elevator to given floor (consumes energy)
    /**
     * @name getContainedPeople() const;
     * @author cppp
     * @brief get a list of contained people
     * @return list of person pointers as reference
     */
	const std::list<PersonPtr>& getContainedPeople() const;
    /**
     * @name getNumPeople() const;
     * @author cppp
     * @brief get number of people in elevator
     * @return int
     */
	int getNumPeople() const;								// get number of people in Elevator
    /**
     * @name addPeople(const std::list<PersonPtr>& people);
     * @author cppp
     * @brief add a list of persons by their pointers to the elevator
     */
	void addPeople(const std::list<PersonPtr>& people);		// add people to Elevator
    /**
     * @name removeArrivedPeople();
     * @author cppp
     * @brief removes arrived people from elevator
     * @return list of arrived people
     */
	std::list<PersonPtr> removeArrivedPeople();				// remove people which arrived
private:
	int currentFloor;								// current floor number
	std::list<PersonPtr> containedPeople;			// people currently in elevator
	double energyConsumed;							// energy consumed
};

#endif /* ELEVATOR_HPP_ */
