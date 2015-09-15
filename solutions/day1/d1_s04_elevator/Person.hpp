#ifndef PERSON_HPP_
#define PERSON_HPP_

/**
 * Represents a person with a destination floor.
 */
class Person {
public:
	/**
	 * Create a person with given destination
	 */
	Person(int destinationFloor);
	
	/**
	 * Copy a person
	 */
	Person(const Person& other);
	
	/** Called when this person is destroyed. */
	~Person();
	
	/** Get destination floor of this person */
	int getDestinationFloor() const {
		return destinationFloor;
	}
	
private:
	/** destination floor of this person */
	int destinationFloor;
};

#endif /* PERSON_HPP_ */
