//============================================================================
// Name        : Aufgabe1.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "Employee.hpp"
#include "Student.hpp"
#include "StudentAssistant.hpp"

/** prints person information on console */
void printPersonInfo(const Person* p) {
	cout << p->getInfo() << endl;
}

int main() {
	StudentAssistant andy("Andy", "852741", "Kathrin");
	
	// cout << andy.getInfo() << endl;
	
	printPersonInfo(&andy);
	
	return 0;
}