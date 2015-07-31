#include "Student.hpp"
#include <iostream>
using namespace std;

/** prints person information on console */
void printPersonInfo(const Person* p) {
	cout << p->getInfo() << endl;
}

int main() {
	Person peter("Peter");
	Student laura("Laura", "123456");
	
	printPersonInfo(&peter);
	printPersonInfo(&laura);
	
	Person *pTim = new Student("Tim", "321654");
	delete pTim;
}
