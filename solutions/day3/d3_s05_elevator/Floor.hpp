#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <list>
#include "Person.hpp"

class Floor {
public:
	Floor();
	/** Return number of people on this floor */
	int getNumPeople() const;
	/** return a const reference to list of contained people */
	const std::list<PersonPtr>& getContainedPeople() const;
	/** Add a human to this floor */
	void addWaitingPerson(PersonPtr h);
	/** remove all humans from this floor */
	std::list<PersonPtr> removeAllPeople();
private:
	std::list<PersonPtr> containedPeople;
};

#endif /* FLOOR_HPP_ */
