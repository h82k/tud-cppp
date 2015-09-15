#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>

class Person {
public:
	Person(const std::string& name);		// initialize the name of the person
	virtual ~Person();						// destructor
	virtual std::string getInfo() const;	// get the name of the person
protected:
	std::string name;						// the name of the person
};

#endif /* PERSON_HPP_ */
