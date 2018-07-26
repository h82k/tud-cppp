#ifndef ELEVATOR_HPP_
#define ELEVATOR_HPP_

#include <vector>
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
	Elevator();						// create an elevator at floor 0, no people inside and 0 energy consumed
    /**
     * @name getFloor();
     * @author cppp
     * @brief get number fo floor the elevator is currently at
     * @return int
     */
	int getFloor();					// get number of floor the elevator is currently at
    /**
     * @name getEnergyConsumed();
     * @author cppp
     * @brief returns the consumed energy since the creation
     * @return double
     */
	double getEnergyConsumed();		// get consumed energy
    /**
     * @name moveToFloor(int floor);
     * @author cppp
     * @brief move elevator to the given floor (consumes energy)
     * @param floor the floor number
     */
	void moveToFloor(int floor);	// move the elevator to given floor (consumes energy)
    /**
     * @name getNumPeople();
     * @author cppp
     * @brief get number of people in elevator
     * @return int
     */
	int getNumPeople();				// get number of people in Elevator
    /**
     * @name getPerson(int i);
     * @author cppp
     * @brief get i-th person in elevator
     */
	Person getPerson(int i);		// get i-th person in Elevator
    /**
     * @name addPeople(std::vector<Person> people);
     * @author cppp
     * @brief add a vector of persons to the elevator
     */
	void addPeople(std::vector<Person> people);		// add people to Elevator
    /**
     * @name removeArrivedPeople();
     * @author cppp
     * @brief removes arrived people from elevator
     * @return vector of arrived people
     */
	std::vector<Person> removeArrivedPeople();		// remove people which arrived
private:
	int currentFloor;								// current floor number
	std::vector<Person> containedPeople;			// people currently in elevator
	double energyConsumed;							// energy consumed
};

#endif /* ELEVATOR_HPP_ */
