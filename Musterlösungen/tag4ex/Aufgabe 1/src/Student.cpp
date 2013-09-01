/*
 * Student.cpp
 */

#include "Student.h"

#include <iostream>
using namespace std;

Student::Student(const std::string& name, const std::string& studentID) :
		Person(name), studentID(studentID) {
	cout << "Creating Student " << name << endl;
}

Student::~Student() {
	cout << "Deleting Student " << name << endl;
}

std::string Student::getInfo() const {
	return string("Student ") + name + string("; ") + studentID;
}


