/*
 * StudentAssistant.cpp
 */

#include "StudentAssistant.h"

#include <iostream>
using namespace std;

StudentAssistant::StudentAssistant(const std::string& name, const std::string& studentID, const std::string supervisor) :
		Person(name), Student("Student", studentID), Employee("Employee", supervisor) {
	cout << "Creating StudentAssistant " << name << endl;
}

StudentAssistant::~StudentAssistant() {
	cout << "Deleting StudentAssistant " << Student::name << endl;
}

std::string StudentAssistant::getInfo() const {
	return string("StudentAssistant ") + name + string("; ") + studentID + string("; ") + supervisor;
}

