#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Person.hpp"

class Student: public Person {	// public inheritance
public:
	Student(const std::string& name, const std::string& studentID);		// init name and ID
	virtual ~Student();													// destructor
	virtual std::string getInfo() const;								// override Person::getInfo() - get name and studentID
	//std::string getInfo() override const;								// variant in C++11, which ensures that a superclass declares this method
private:
	std::string studentID;												// the student ID of the student
};

#endif /* STUDENT_HPP_ */
