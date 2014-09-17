/*
 * Person.h
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>

class Person {
public:
	Person(const std::string& name);
	virtual ~Person();
	
	virtual std::string getInfo() const;
	
protected:
	std::string name;
};

#endif /* PERSON_H_ */
