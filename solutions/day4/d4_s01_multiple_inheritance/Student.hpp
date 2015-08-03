#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Person.hpp"

class Student: public virtual Person {
public:
	Student(const std::string& name, const std::string& studentID);
	virtual ~Student();
	virtual std::string getInfo() const;
protected:
	std::string studentID;
};

#endif /* STUDENT_HPP_ */
