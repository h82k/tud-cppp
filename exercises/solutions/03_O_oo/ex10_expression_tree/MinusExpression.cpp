#include "MinusExpression.hpp"
#include <iostream>

MinusExpression::~MinusExpression() {
	std::cout << "Deleting MinusExpression" << std::endl;
}

MinusExpression::MinusExpression(Expression *left, Expression *right):
	BinaryExpression(left, right)
{
	std::cout << "creating MinusExpression" << std::endl;
}

double MinusExpression::compute() {
	return left->compute() - right->compute();
}

