#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <vector>
#include "Person.hpp"

/**
 * @name Floor
 * @author cppp
 * @brief class describing a building's floor
 */
class Floor {
public:
    /**
     * @name getNumPeople();
     * @author cppp
     * @brief get number of people of this floor
     * @return int number of people
     */
	int getNumPeople();						// get the number of people on this floor
    /**
     * @name getPerson(int i);
     * @author cppp
     * @brief get the i-th person on floor
     * @param i the person's index
     * @return Person
     */
	Person getPerson(int i);				// get the i-th person on this floor
    /**
     * @name addWaitingPerson(Person h);
     * @author cppp
     * @brief adding a person to this floor
     * @param h the waiting person
     */
	void addWaitingPerson(Person h);		// add a person to this floor
    /**
     * @name removeAllPeople();
     * @author cppp
     * @brief remove all persons from this floor
     * @return all removed persons in vector
     */
	std::vector<Person> removeAllPeople();	// remove all persons from this floor
private:
	std::vector<Person> containedPeople;	// persons on this floor
};

#endif /* FLOOR_HPP_ */
