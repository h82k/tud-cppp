#include "NumberExpression.hpp"
#include "PlusExpression.hpp"
#include "MinusExpression.hpp"
#include <iostream>

int main() {
	PlusExpression e(new MinusExpression(new NumberExpression(42), new NumberExpression(12)), new NumberExpression(10));
	std::cout << e.compute() << std::endl; // should be 40
}
