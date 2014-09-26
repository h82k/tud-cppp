/*
 * Dish.cpp
 *
 *  Created on: 01.08.2013
 *      Author: anjorin
 */

#include <iostream>
#include "Dish.h"

Dish::Dish(const string& name) : name(name) {
	cout <<  "Dish(" << name << ")" << endl;
}

Dish::~Dish() {
	cout <<  "~Dish(" << name << ")" << endl;
}

