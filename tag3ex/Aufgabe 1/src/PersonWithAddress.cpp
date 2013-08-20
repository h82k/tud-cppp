/*
 * PersonWithAddress.cpp
 */

#include "PersonWithAddress.h"

PersonWithAddress::PersonWithAddress(std::string name, std::string address) :
		Person(name), address(address) {
	cout << "Creating PersonWithAddress " << name << "; " << address << endl;
}

PersonWithAddress::~PersonWithAddress() {
	cout << "Deleting PersonWithAddress" << name << "; " << address << endl;
}

std::string PersonWithAddress::getInfo() const {
	return string("PersonWithAddress ") + name + string("; ") + address;
}
