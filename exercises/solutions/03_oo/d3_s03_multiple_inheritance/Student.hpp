#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Person.hpp"

/**
 * @name Student
 * @author cppp
 * @brief describes a student
 */
class Student: public virtual Person {
public:
    /**
     * @name Student(const std::string& name, const std::string& studentID);
     * @author cppp
     * @brief constructor student initializing name and studentid
     */
	Student(const std::string& name, const std::string& studentID);
    /**
     * @name ~Student();
     * @author cppp
     * @brief destructor of the student object
     */
	virtual ~Student();
    /**
     * @name getInfo();
     * @author cppp
     * @brief returns string holding the name and studentid
     * @return std::string
     */
	virtual std::string getInfo() const;
protected:
	std::string studentID;
};

#endif /* STUDENT_HPP_ */
