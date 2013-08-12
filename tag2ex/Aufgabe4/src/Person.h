/*
 * Person.h
 *
 *  Created on: May 14, 2013
 *      Author: jgdo
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <boost/shared_ptr.hpp>

class Person {
public:
	Person(int destinationFloor);
	~Person();
	
	inline int destinationFloor() {
		return destinationFloor_;
	}
	
private:
	int destinationFloor_;
};

typedef boost::shared_ptr<Person> PersonPtr;

#endif /* PERSON_H_ */
