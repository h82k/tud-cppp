/*
 * NumberExpression.h
 */

#ifndef NUMBEREXPRESSION_H_
#define NUMBEREXPRESSION_H_

#include "Expression.h"

class NumberExpression: public Expression {
public:
	NumberExpression(double n);
	virtual ~NumberExpression();

	virtual double compute();

private:
	double number;
};

#endif /* NUMBEREXPRESSION_H_ */
