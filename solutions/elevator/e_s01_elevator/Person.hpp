#ifndef PERSON_HPP_
#define PERSON_HPP_

class Person {
public:
	Person(int destinationFloor);		// create a person with given destination
	Person(const Person& other);		// copy constructor
	~Person();							// destructor
	int getDestinationFloor() const;	// get the destination floor of this person
private:
	int destinationFloor;				// destination floor of this person
};

#endif /* PERSON_HPP_ */
