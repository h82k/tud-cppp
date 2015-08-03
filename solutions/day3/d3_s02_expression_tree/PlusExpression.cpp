#include "PlusExpression.hpp"
#include <iostream>

PlusExpression::~PlusExpression() {
	std::cout << "Deleting PlusExpression" << std::endl;
}

PlusExpression::PlusExpression(Expression *left, Expression *right):
	BinaryExpression(left, right)
{
	std::cout << "creating PlusExpression" << std::endl;
}

double PlusExpression::compute() {
	return left->compute() + right->compute();
}
