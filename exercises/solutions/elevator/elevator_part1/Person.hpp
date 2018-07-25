#ifndef PERSON_HPP_
#define PERSON_HPP_

/**
 * @name Person
 * @author cppp
 * @brief class describing a person
 */
class Person {
public:
    /**
     * @name Person(int destinationFloor);
     * @author cppp
     * @brief constructor with desired destination floor
     * @param destinationFloor the destination floor of created person object
     */
	Person(int destinationFloor);		// create a person with given destination
    /**
     * @name Person(const Person& other);
     * @author cppp
     * @brief copy constructor
     * @param other person to copy
     */
	Person(const Person& other);		// copy constructor
    /**
     * @name ~Person();
     * @author cppp
     * @brief destructor
     */
	~Person();							// destructor
    /**
     * @name getDestinationFloor() const;
     * @author cppp
     * @brief get the destination floor of this person
     * @return const int
     */
	int getDestinationFloor() const;	// get the destination floor of this person
private:
	int destinationFloor;				// destination floor of this person
};

#endif /* PERSON_HPP_ */
