#ifndef STUDENTASSISTANT_HPP_
#define STUDENTASSISTANT_HPP_

#include "Employee.hpp"
#include "Student.hpp"

/**
 * @name StudentAssistant
 * @author cppp
 * @brief describes a student assistant 
 */
class StudentAssistant: public Student, public Employee {
public:
    /**
     * @name StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor);
     * @author cppp
     * @brief constructor of student assistant initializing a name, studentid and supervisor
     */
	StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor);
    /**
     * @name ~StudentAssistant();
     * @author cppp
     * @brief destructor of the student assistent object
     */
	virtual ~StudentAssistant();
    /**
     * @name getInfo();
     * @author cppp
     * @brief returns string holding the name, studentid and supervisor
     * @return std::string
     */
	virtual std::string getInfo() const;
};

#endif /* STUDENTASSISTANT_HPP_ */
