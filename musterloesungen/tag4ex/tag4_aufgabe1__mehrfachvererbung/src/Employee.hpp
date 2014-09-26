/*
 * Employee.hpp
 */

#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include "Person.hpp"

class Employee: public virtual Person {
public:
	Employee(const std::string& name, const std::string& supervisor);
	virtual ~Employee();
	
	virtual std::string getInfo() const;
protected:
	std::string supervisor;
};

#endif /* EMPLOYEE_HPP_ */
