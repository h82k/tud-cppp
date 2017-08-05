#include "NumberExpression.hpp"
#include <iostream>

NumberExpression::NumberExpression(double n):
	number(n)
{
	std::cout << "Creating NumberExpression" << std::endl;
}

NumberExpression::~NumberExpression() {
	std::cout << "Deleting NumberExpression" << std::endl;
}

double NumberExpression::compute() {
	return number;
}
