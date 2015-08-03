#include "Person.hpp"
#include <iostream>

Person::Person(const std::string& name):
	name(name)
{
	std::cout << "Creating Person " << name << std::endl;
}

Person::~Person() {
	std::cout << "Deleting Person " << name << std::endl;
}

std::string Person::getInfo() const {
	return string("Person ") + name;
}

