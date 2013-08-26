/*
 * BinaryExpression.h
 */

#ifndef BINARYEXPRESSION_H_
#define BINARYEXPRESSION_H_

#include "Expression.h"

class BinaryExpression: public Expression {
public:
	BinaryExpression(Expression *left, Expression *right);
	virtual ~BinaryExpression();

protected:
	Expression *left, *right;
};

#endif /* BINARYEXPRESSION_H_ */
