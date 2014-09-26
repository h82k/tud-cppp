#ifndef FLOOR_H_
#define FLOOR_H_

#include <vector>

#include "Person.h"

class Floor {
public:
	void addPerson(const Person &person);
private:
	std::vector<Person> containedPersons;
};

#endif /* FLOOR_H_ */
