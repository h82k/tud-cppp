/*
 * Student.h
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "Person.h"

class Student: public Person {
public:
	Student(const std::string& name, const std::string& studentID);
	virtual ~Student();

	virtual std::string getInfo() const;
	
private:
	std::string studentID;
};

#endif /* STUDENT_H_ */
