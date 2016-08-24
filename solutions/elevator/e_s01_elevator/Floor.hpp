#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <vector>
#include "Person.hpp"

class Floor {
public:
	int getNumPeople();						// get the number of people on this floor
	Person getPerson(int i);				// get the i-th person on this floor
	void addWaitingPerson(Person h);		// add a person to this floor
	std::vector<Person> removeAllPeople();	// remove all persons from this floor
private:
	std::vector<Person> containedPeople;	// persons on this floor
};

#endif /* FLOOR_HPP_ */
