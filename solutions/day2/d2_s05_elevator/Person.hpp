#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <memory>

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

typedef std::shared_ptr<Person> PersonPtr;

#endif /* PERSON_HPP_ */
