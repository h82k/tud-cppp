/*
 * PersonWithAddress.h
 */

#ifndef PERSONWITHADDRESS_H_
#define PERSONWITHADDRESS_H_

#include "Person.h"

#include <iostream>
using namespace std;

class PersonWithAddress: public Person {
public:
	PersonWithAddress(std::string name, std::string address);
	virtual ~PersonWithAddress();

	std::string getInfo() const;
	
protected:
	std::string address;
};

#endif /* PERSONWITHADDRESS_H_ */
