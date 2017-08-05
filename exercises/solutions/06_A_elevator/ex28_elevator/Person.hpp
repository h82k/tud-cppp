#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <memory>

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
     * @name getDestinationFloor() const;
     * @author cppp
     * @brief get the destination floor of this person
     * @return const int
     */
	int getDestinationFloor() const;	// get the destination floor of this person
    /**
     * @name ~Person();
     * @author cppp
     * @brief destructor
     */
	~Person();							// destructor
private:
	int destinationFloor;				// destination floor of this person
};

typedef std::shared_ptr<Person> PersonPtr;

#endif /* PERSON_HPP_ */
