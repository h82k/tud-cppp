/*
 * MinusExpression.h
 */

#ifndef MINUSEXPRESSION_H_
#define MINUSEXPRESSION_H_

#include "BinaryExpression.h"

class MinusExpression: public BinaryExpression {
public:
	MinusExpression(Expression *left, Expression *right);
	virtual ~MinusExpression();
	
	virtual double compute();
private:
};

#endif /* MINUSEXPRESSION_H_ */
