/*
 * Floor.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include <vector>
#include <set>

#include "Person.h"

class Floor {
public:
	Floor();

	/** Return number of people on this floor */
	inline int getNumPeople() {
		return containedPeople_.size();
	}
	
	/** return i-th human on this floor */
	inline Person getHuman(int i) {
		return containedPeople_.at(i);
	}
	
	/** Add a human to this floor */
	void addWaitingHuman(Person h);
	
	/** remove all humans from this floor */
	std::vector<Person> removeAllPeople();

private:
	std::vector<Person> containedPeople_;
};

#endif /* FLOOR_H_ */
