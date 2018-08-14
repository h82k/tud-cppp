#include "BinaryExpression.hpp"
#include <iostream>

BinaryExpression::BinaryExpression(Expression *left, Expression *right) :
		left(left), right(right) {
	std::cout << "creating BinaryExpression" << std::endl;
}

BinaryExpression::~BinaryExpression() {
	/*
	 * You may also delete the left and right child pointers here, but
	 * this may be dangerous if you, for example, reuse Expressions
	 * as children of multiple BinaryExpressions because such Expresssions
	 * may be deleted multiple times.
	 */
//	delete left; // assume they are valid
//	delete right;
	std::cout << "Deleting BinaryExpression" << std::endl;
}

