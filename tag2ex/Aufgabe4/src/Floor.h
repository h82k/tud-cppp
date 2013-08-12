/*
 * Floor.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include <list>
#include <set>

#include "Person.h"

class Floor {
public:
	Floor();

	/** Return number of people on this floor */
	inline int getNumPeople() {
		return containedPeople.size();
	}
	
	/** return a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const {
		return containedPeople;
	}
	
	/** Add a human to this floor */
	void addWaitingHuman(PersonPtr h);
	
	/** remove all humans from this floor */
	std::list<PersonPtr> removeAllPeople();

private:
	std::list<PersonPtr> containedPeople;
};

#endif /* FLOOR_H_ */
