#include "StudentAssistant.hpp"
#include <iostream>

StudentAssistant::StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor):
	Person(name), Student("Student", studentID), Employee("Employee", supervisor)
{
	std::cout << "Creating StudentAssistant " << name << std::endl;
}

StudentAssistant::~StudentAssistant() {
	std::cout << "Deleting StudentAssistant " << Student::name << std::endl;
}

std::string StudentAssistant::getInfo() const {
	return std::string("StudentAssistant ") + name + std::string("; ") + studentID + std::string("; ") + supervisor;
}

