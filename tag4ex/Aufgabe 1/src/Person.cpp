/*
 * Person.cpp
 */

#include "Person.h"

#include <iostream>
using namespace std;

Person::Person(const std::string& name) :
		name(name) {
	cout << "Creating Person " << name << endl;
}

Person::~Person() {
	cout << "Deleting Person " << name << endl;
}

std::string Person::getInfo() const {
	return string("Person ") + name;
}

