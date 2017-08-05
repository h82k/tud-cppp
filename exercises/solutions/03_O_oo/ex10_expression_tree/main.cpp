#include "NumberExpression.hpp"
#include "PlusExpression.hpp"
#include "MinusExpression.hpp"
#include <iostream>

/**
 * General note:
 * You could also implement the tree using either references, copy-by-value (not recommended), or std::shared_ptr
 */
int main() {
	NumberExpression* num42 = new NumberExpression(42);
	NumberExpression* num12 = new NumberExpression(12);
	NumberExpression* num10 = new NumberExpression(10);
	MinusExpression* minusExpression = new MinusExpression(num42, num12);

	PlusExpression e(minusExpression, num10);
	std::cout << e.compute() << std::endl; // should be 40

	/**
	 * Note: If possible, you should delete memory in the same scope that also contains the call to new.
	 *
	 * An alternative would be to make BinaryExpression::~BinaryExpression delete its left and right child,
	 * but this would mean
	 * (i) that you restrict the whole ExpressionTree to always use objects on the heap and
	 * (ii) that you cannot reuse NumberExpressions even though they are immutable/constant
	 */
	delete num42;
	delete num12;
	delete num10;
	delete minusExpression;
}
