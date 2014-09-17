/*
 * Employee.cpp
 */

#include "Employee.h"

#include <iostream>
using namespace std;

Employee::Employee(const std::string& name, const std::string& supervisor) :
		Person(name), supervisor(supervisor) {
	cout << "Creating Employee " << name << endl;
}

Employee::~Employee() {
	cout << "Deleting Employee " << name << endl;
}

std::string Employee::getInfo() const {
	return string("Employee ") + name + string("; ") + supervisor;
}

