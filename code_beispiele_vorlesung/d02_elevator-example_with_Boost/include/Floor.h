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

#include "Human.h"

class Floor {
public:
	Floor();

	inline const std::list<HumanPtr>& getWaitingPeople() const {
		return containedPeople_;
	}
	
	inline bool hasPeopleWaiting() const {
		return !containedPeople_.empty();
	}
	
	void addWaitingPeople(const std::list<HumanPtr>& people);
	std::list<HumanPtr> removeAllPeople();
	
	
	std::set<int> getDestinationFloors() const;

private:
	std::list<HumanPtr> containedPeople_;
};

#endif /* FLOOR_H_ */
