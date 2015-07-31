#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>

class Person {
public:
	Person(const std::string& name);
	virtual ~Person();
	virtual std::string getInfo() const;
protected:
	std::string name;
};

#endif /* PERSON_HPP_ */
