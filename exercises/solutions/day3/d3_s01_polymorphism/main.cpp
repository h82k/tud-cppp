#include "Student.hpp"
#include <iostream>

/** prints person information on console */
void printPersonInfo(const Person* p) {
	std::cout << p->getInfo() << std::endl;
}

int main() {
	Person peter("Peter");
	Student laura("Laura", "123456");
	
	printPersonInfo(&peter);
	printPersonInfo(&laura);
	
	Person *pTim = new Student("Tim", "321654");
	delete pTim;
}
