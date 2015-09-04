#include "Student.hpp"
#include <iostream>

Student::Student(const std::string& name, const std::string& studentID):
	Person(name), studentID(studentID)
{
	std::cout << "Creating Student " << name << std::endl;
}

Student::~Student() {
	std::cout << "Deleting Student " << name << std::endl;
}

std::string Student::getInfo() const {
	return std::string("Student ") + name + std::string("; ") + studentID;
}


