#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <string>

/**
 * @name Person();
 * @author cppp
 * @brief person class
 */
class Person {
public:
    /**
     * @name Person(const std::string& name);
     * @author cppp
     * @brief constructor of person object, initializing name
     * @param name the initial name
     */
	Person(const std::string& name);
    /**
     * @name ~Person();
     * @author cppp
     * @brief virtual person destructor
     */
	virtual ~Person();
    /**
     * @name getInfo();
     * @author cppp
     * @brief returns string holding the name
     * @return std::string
     */
	virtual std::string getInfo() const;
protected:
	std::string name;
};

#endif /* PERSON_HPP_ */
