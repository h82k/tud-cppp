/*
 * Person.h
 *
 *  Created on: 01.08.2013
 *      Author: anjorin
 */

#ifndef PERSON_H_
#define PERSON_H_

#include<string>

using namespace std;

class Person {
public:
	Person(const string& name, int weight);
	~Person();

	inline const string& getName() const {
		return name;
	}

	inline int getWeight() const {
		return weight;
	}

private:
	const string name;
	int weight;
};

#endif /* PERSON_H_ */
