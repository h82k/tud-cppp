#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <memory>

class Person {
public:
	Person(int destinationFloor);		// create a person with given destination
	~Person();							// destructor
	int getDestinationFloor() const;	// get the destination floor of this person
private:
	int destinationFloor;				// destination floor of this person
};

typedef std::shared_ptr<Person> PersonPtr;

#endif /* PERSON_HPP_ */
