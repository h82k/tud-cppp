#ifndef BINARYEXPRESSION_HPP_
#define BINARYEXPRESSION_HPP_

#include "Expression.hpp"

class BinaryExpression: public Expression {
public:
	BinaryExpression(Expression *left, Expression *right);
	virtual ~BinaryExpression();
protected:
	Expression *left, *right;
};

#endif /* BINARYEXPRESSION_HPP_ */
