/*
 * NumberExpression.hpp
 */

#ifndef NUMBEREXPRESSION_HPP_
#define NUMBEREXPRESSION_HPP_

#include "Expression.hpp"

class NumberExpression: public Expression {
public:
	NumberExpression(double n);
	virtual ~NumberExpression();

	virtual double compute();

private:
	double number;
};

#endif /* NUMBEREXPRESSION_HPP_ */
