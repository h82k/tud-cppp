#include "Employee.hpp"
#include "Student.hpp"
#include "StudentAssistant.hpp"
#include <iostream>
using namespace std;

/** prints person information on console */
void printPersonInfo(const Person* p) {
	cout << p->getInfo() << endl;
}

int main() {
	StudentAssistant andy("Andy", "852741", "Kathrin");
	// cout << andy.getInfo() << endl;
	printPersonInfo(&andy);
}
