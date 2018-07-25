#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "Person.hpp"

/**
 * @name Student
 * @author cppp
 * @brief student class inherits the person class publicly
 * @sa Person
 */
class Student: public Person {	// public inheritance
public:
    /**
     * @name Student(const std::string& name, const std::string& studentID);
     * @author cppp
     * @brief constructor of student object with name and studentid
     * @param name the initial name of the student object
     * @param studentid the initial studentid of the student object
     */
	Student(const std::string& name, const std::string& studentID);		// init name and ID
    /**
     * @name ~Student();
     * @author cppp
     * @brief destructor of student object
     */
	virtual ~Student();													// destructor
    /**
     * @name getInfo() const;
     * @author cppp
     * @brief returns a string containing the name and studentid
     */
	virtual std::string getInfo() const;								// Person::getInfo() - get name and studentID
	//std::string getInfo() const override;								// variant in C++11, which ensures that a superclass declares this method
private:
	std::string studentID;												// the student ID of the student
};

#endif /* STUDENT_HPP_ */
