/*
 * Person.h
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <boost/shared_ptr.hpp>

class Person {
public:
	Person(int destinationFloor);
	~Person();

	inline int getDestinationFloor() const {
		return destinationFloor;
	}
	
private:
	int destinationFloor;
};

typedef boost::shared_ptr<Person> PersonPtr;

#endif /* PERSON_H_ */
