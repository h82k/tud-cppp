//====================================
// Name: elevator-example-lecture.cpp
//====================================

#include <iostream>
using namespace std;

#include "Person.h"

void makeSmallTalkWith(const Person& person){
	cout << "Isn't the weather quite pleasant today, " << person.getName() << "?" << endl;
}

void greet(const Person& person){
	cout << "Greeting " << person.getName() << endl;
	makeSmallTalkWith(person);

	Person* passerBy = new Person("Sir");
	makeSmallTalkWith(*passerBy);

	delete passerBy;
	passerBy = 0;
}

void moveToNextFloor(int strategy){
	switch(strategy){
		case 0:
			cout << "Choose next floor to minimize energy." << endl;
			break;
		case 1:
			cout << "Choose next floor to minimize waiting time." << endl;
			break;
		// and so on ...
	}
}


int main() {
	Person* eve(new Person("Eve"));
	greet(*eve);

	Person* alice = eve;
	greet(*alice);

	delete eve;
	eve = 0;
}

