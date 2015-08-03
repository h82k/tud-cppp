#include "BinaryExpression.hpp"
#include <iostream>

BinaryExpression::BinaryExpression(Expression *left, Expression *right): left(left), right(right) {
	std::cout << "creating BinaryExpression" << std::endl;
}

BinaryExpression::~BinaryExpression() {
	delete left; // assume they are valid
	delete right;
	std::cout << "Deleting BinaryExpression" << std::endl;
}

