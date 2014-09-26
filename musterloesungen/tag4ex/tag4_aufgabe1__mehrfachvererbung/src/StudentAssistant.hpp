/*
 * StudentAssistant.hpp
 */

#ifndef STUDENTASSISTANT_HPP_
#define STUDENTASSISTANT_HPP_

#include "Employee.hpp"
#include "Student.hpp"

class StudentAssistant: public Student, public Employee {
public:
	StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor);
	virtual ~StudentAssistant();
	
	virtual std::string getInfo() const;
};

#endif /* STUDENTASSISTANT_HPP_ */
