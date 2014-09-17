/*
 * PlusExpression.cpp
 */

#include "PlusExpression.h"

#include <iostream>
using namespace std;

PlusExpression::~PlusExpression() {
	cout << "Deleting PlusExpression" << endl;
}

PlusExpression::PlusExpression(Expression *left, Expression *right) :
		BinaryExpression(left, right) {
	cout << "creating PlusExpression" << endl;
}

double PlusExpression::compute() {
	return left->compute() + right->compute();
}
