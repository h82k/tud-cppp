#include "Employee.hpp"
#include <iostream>

Employee::Employee(const std::string& name, const std::string& supervisor):
	Person(name), supervisor(supervisor)
{
	std::cout << "Creating Employee " << name << std::endl;
}

Employee::~Employee() {
	std::cout << "Deleting Employee " << name << std::endl;
}

std::string Employee::getInfo() const {
	return string("Employee ") + name + string("; ") + supervisor;
}

