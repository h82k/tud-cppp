#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <list>
#include "Person.hpp"

/**
 * @name Floor
 * @author cppp
 * @brief class describing a building's floor
 */
class Floor {
public:
    /**
     * @name Floor();
     * @author cppp;
     * @brief constructor of floor
     */
	Floor();
    /**
     * @name getNumPeople() const;
     * @author cppp;
     * @brief returns the number of people on floor as int
     * @return int -> waiting people
     */
	int getNumPeople() const;				// get the number of people on this floor
    /**
     * @name getContainedPeople() const;
     * @author cppp;
     * @brief returns a constant list of personptrs which are waiting on floor
     * @return waiting people as personptrs in list
     */
	const std::list<PersonPtr>& getContainedPeople() const;
    /**
     * @name addWaitingPerson(PersonPtr h);
     * @author cppp;
     * @brief adding a person to the waiting list (this->containedPeople)
     * @param h person to add as personptr
     */
	void addWaitingPerson(PersonPtr h);		// add a person to this floor
    /**
     * @name removeAllPeople();
     * @author cppp;
     * @brief remove all people from floor and returning them as list of personptrs
     * @return list of personptr
     */
	std::list<PersonPtr> removeAllPeople();	// remove all persons from this floor
private:
	std::list<PersonPtr> containedPeople;	// persons on this floor
};

#endif /* FLOOR_HPP_ */
