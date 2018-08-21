/*
 * Person.cpp
 *
 *  Created on: 01.08.2013
 *      Author: anjorin
 */

#include <iostream>
#include "Person.h"

using namespace std;

Person::Person(const string& name, int weight) : name(name), weight(weight) {
	cout << "Person(" << name << "," << weight << ")" <<  endl;
}

Person::~Person() {
	cout << "~Person(" << name << "," << weight << ")" << endl;
}

