#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <list>
#include "Person.hpp"

class Floor {
public:
	Floor();
	int getNumPeople() const;				// get the number of people on this floor
	const std::list<PersonPtr>& getContainedPeople() const;
	void addWaitingPerson(PersonPtr h);		// add a person to this floor
	std::list<PersonPtr> removeAllPeople();	// remove all persons from this floor
private:
	std::list<PersonPtr> containedPeople;	// persons on this floor
};

#endif /* FLOOR_HPP_ */
