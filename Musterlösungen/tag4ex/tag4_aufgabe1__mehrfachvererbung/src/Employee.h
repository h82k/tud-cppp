/*
 * Employee.h
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include "Person.h"

class Employee: public virtual Person {
public:
	Employee(const std::string& name, const std::string& supervisor);
	virtual ~Employee();
	
	virtual std::string getInfo() const;
protected:
	std::string supervisor;
};

#endif /* EMPLOYEE_H_ */
