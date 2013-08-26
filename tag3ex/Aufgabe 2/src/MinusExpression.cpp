/*
 * PlusExpression.cpp
 */

#include "MinusExpression.h"

#include <iostream>
using namespace std;

MinusExpression::~MinusExpression() {
	cout << "Deleting MinusExpression" << endl;
}

MinusExpression::MinusExpression(Expression *left, Expression *right) :
		BinaryExpression(left, right) {
	cout << "creating MinusExpression" << endl;
}

double MinusExpression::compute() {
	return left->compute() - right->compute();
}

