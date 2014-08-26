#include "Person.h"
#include "Floor.h"
#include "Elevator.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Person eve("Eve", 55.0); // initial weight: 55kg
	Person bob("Bob", 80.0); // initial weight: 80kg

	cout << bob.getName() << " has weight " << bob.getWeight() << endl;

	Person::makeFriends(eve, bob);

	Person &bobAsEvesFriend = eve.getFriends().at(0);
	bobAsEvesFriend.setWeight(95);
	cout << bobAsEvesFriend.getName() << " [as Eve's friend] has weight " << bobAsEvesFriend.getWeight() << endl;
	cout << bob.getName() << " has weight " << bob.getWeight() << endl;
}
