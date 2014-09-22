/*
 * BinaryExpression.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: jgdo
 */

#include "BinaryExpression.hpp"

#include <iostream>

using namespace std;

BinaryExpression::BinaryExpression(Expression *left, Expression *right): left(left), right(right) {
	cout << "creating BinaryExpression" << endl; 	
}

BinaryExpression::~BinaryExpression() {
	delete left; // assume they are valid
	delete right;
	cout << "Deleting BinaryExpression" << endl; 
}

