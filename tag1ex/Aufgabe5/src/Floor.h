/*
 * Floor.h
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include <vector>
#include <set>

#include "Person.h"

/**
 * Represents a building floor with waiting people.
 */
class Floor {
public:
	/** Return number of people on this floor */
	inline int getNumPeople() {
		return containedPeople.size();
	}
	
	/** return i-th person on this floor */
	inline Person getPerson(int i) {
		return containedPeople.at(i);
	}
	
	/** Add a person to this floor */
	void addWaitingPerson(Person h);
	
	/** remove all humans from this floor */
	std::vector<Person> removeAllPeople();
private:
	std::vector<Person> containedPeople;
};

#endif /* FLOOR_H_ */
