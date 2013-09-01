/*
 * PlusExpression.h
 */

#ifndef PLUSEXPRESSION_H_
#define PLUSEXPRESSION_H_

#include "BinaryExpression.h"

class PlusExpression: public BinaryExpression {
public:
	PlusExpression(Expression *left, Expression *right);
	virtual ~PlusExpression();

	virtual double compute();
};

#endif /* PLUSEXPRESSION_H_ */
