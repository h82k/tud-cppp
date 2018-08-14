#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>

/**
 * @name Person
 * @author cppp
 * @brief Person class describes a person using a name
 */
class Person {
public:
    /**
     * @name Person(const std::string& name);
     * @author cppp
     * @brief constructor initializes a with a name
     * @param name the initial name of the person object
     */
	Person(const std::string& name);		// initialize the name of the person
    /**
     * @name ~Person();
     * @author cppp
     * @brief virtual destructor of person object
     */
	virtual ~Person();						// destructor
    /**
     * @name getInfo();
     * @author cppp
     * @brief returns the name of a person
     * @return the person objects name attribute
     */
	virtual std::string getInfo() const;	// get the name of the person
protected:
	std::string name;						// the name of the person
};

#endif /* PERSON_HPP_ */
