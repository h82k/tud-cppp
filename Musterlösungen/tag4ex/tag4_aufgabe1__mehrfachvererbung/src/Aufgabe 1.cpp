//============================================================================
// Name        : Aufgabe 1.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "Employee.h"
#include "Student.h"
#include "StudentAssistant.h"

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
