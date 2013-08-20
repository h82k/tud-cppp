//============================================================================
// Name        : Aufgabe 1.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "PersonWithAddress.h"

/** prints person information on console */
void printPersonInfo(const Person* p) {
	cout << p->getInfo() << endl;
}

int main() {
	Person max("Max");
	PersonWithAddress peter("Peter", "Berlin");
	
	cout << max.getInfo() << endl;
	cout << peter.getInfo() << endl;
	
	printPersonInfo(&max);
	printPersonInfo(&peter);
	
	Person *p = new PersonWithAddress("Laura", "Haumburg");
	delete p;
}
