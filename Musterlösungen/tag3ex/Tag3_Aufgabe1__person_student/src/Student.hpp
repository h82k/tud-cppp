/*
 * Student.hpp
 */

#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Person.hpp"

class Student: public Person {
public:
	Student(const std::string& name, const std::string& studentID);
	virtual ~Student();

	virtual std::string getInfo() const;
	
private:
	std::string studentID;
};

#endif /* STUDENT_HPP_ */
