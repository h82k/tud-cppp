/*
 * Person.h
 */

#ifndef PERSON_H_
#define PERSON_H_

/*
 * Represents a person with a destination floor.
 */
class Person {
public:
	/**
	 * Create a person with given destination
	 */
	Person(int destinationFloor);

	/** Called when this person is destroyed. */
	~Person();

	/** Get destination floor of this person */
	inline int getDestinationFloor() {
		return destinationFloor;
	}
	
private:
	/** destination floor of this person */
	int destinationFloor;
};

#endif /* PERSON_H_ */
