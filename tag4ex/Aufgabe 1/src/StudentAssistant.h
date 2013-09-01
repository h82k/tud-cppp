/*
 * StudentAssistant.h
 */

#ifndef STUDENTASSISTANT_H_
#define STUDENTASSISTANT_H_

#include "Employee.h"
#include "Student.h"

class StudentAssistant: public Student, public Employee {
public:
	StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor);
	virtual ~StudentAssistant();
	
	virtual std::string getInfo() const;
};

#endif /* STUDENTASSISTANT_H_ */
