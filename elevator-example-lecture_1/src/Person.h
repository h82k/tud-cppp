/*
 * Person.h
 *
 *  Created on: 12.07.2013
 *      Author: anjorin
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
using namespace std;

#include <boost/shared_ptr.hpp>

class Person {
public:
	Person(const string& name);
	Person(const Person& person);
	~Person();

	inline const string& getName() const {
		return name;
	}

private:
	const string name;
};

//typedef boost::shared_ptr<Person> PersonPtr;
//typedef boost::shared_ptr<const Person> ConstPersonPtr;

#endif /* PERSON_H_ */
