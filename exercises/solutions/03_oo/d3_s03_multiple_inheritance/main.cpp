#include "Employee.hpp"
#include "Student.hpp"
#include "StudentAssistant.hpp"
#include <iostream>

/** prints person information on console */
void printPersonInfo(const Person* p) {
	std::cout << p->getInfo() << std::endl;
}

int main() {
	StudentAssistant andy("Andy", "852741", "Kathrin");
	// std::cout << andy.getInfo() << std::endl;
	printPersonInfo(&andy);
}
