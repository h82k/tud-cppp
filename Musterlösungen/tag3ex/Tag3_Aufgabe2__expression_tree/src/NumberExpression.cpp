/*
 * NumberExpression.cpp
 */

#include "NumberExpression.h"

#include <iostream>
using namespace std;

NumberExpression::NumberExpression(double n) :
		number(n) {
	cout << "Creating NumberExpression" << endl;
}

NumberExpression::~NumberExpression() {
	cout << "Deleting NumberExpression" << endl;
}

double NumberExpression::compute() {
	return number;
}
