/*
 * main.cpp
 *
 *  Created on: 01.08.2013
 *      Author: anjorin
 */

#include "Elevator.h"
#include "Dish.h"
#include "Person.h"
#include <string>

using namespace std;

template<class S, class T>
S totalWeight(T* start, T* end, string things){
	S total = 0;

	while(start != end){
		total += start++->getWeight();
	}

	cout << "Total weight of " << things << " is " << total;
	cout << endl;

	return total;
}

int main(int argc, char **argv) {
	Elevator<> elevator;

	Person people[] = {Person("Tony", 75), Person("Lukas", 14)};
	elevator.placeInElevator(people);
	elevator.placeInElevator(people + 1);

	int totalAsInt = totalWeight<int, Person>(people, people + 2, "people");

	// :~

	Elevator<Dish> dumbwaiter;

	Dish dishes[] = {Dish("Jollof Rice"), Dish("Roasted Chicken")};

	dumbwaiter.placeInElevator(dishes);
	dumbwaiter.placeInElevator(dishes + 1);

	double totalAsDouble = totalWeight<double, Dish>(dishes, dishes + 2, "dishes");
}
