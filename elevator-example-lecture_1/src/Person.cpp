/*
 * Person.cpp
 *
 *  Created on: 12.07.2013
 *      Author: anjorin
 */

#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(const string& name): name(name) {
	cout << "Created " << name << endl;
}

Person::Person(const Person& person): name(person.name){
	cout << "Cloning " << name << endl;
}

Person::~Person() {
	cout << "Good bye " << name << endl;
}

