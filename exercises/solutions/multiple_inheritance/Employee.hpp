#ifndef EMPLOYEE_HPP_
#define EMPLOYEE_HPP_

#include "Person.hpp"

/**
 * @name Employee
 * @author cppp
 * @brief describes an employee
 */
class Employee: public virtual Person {
public:
    /**
     * @name Employee(const std::string& name, const std::string& supervisor);
     * @author cppp
     * @brief constructor of employee, initializing name and supervisor
     */
	Employee(const std::string& name, const std::string& supervisor);
    /**
     * @name ~Employee();
     * @author cppp
     * @brief destructor of employee
     */
	virtual ~Employee();
    /**
     * @name getInfo();
     * @author cppp
     * @brief returns string holding the name and supervisor
     * @return std::string
     */
	virtual std::string getInfo() const;
protected:
	std::string supervisor;
};

#endif /* EMPLOYEE_HPP_ */
