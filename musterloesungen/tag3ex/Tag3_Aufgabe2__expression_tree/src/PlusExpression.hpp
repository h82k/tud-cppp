/*
 * PlusExpression.hpp
 */

#ifndef PLUSEXPRESSION_HPP_
#define PLUSEXPRESSION_HPP_

#include "BinaryExpression.hpp"

class PlusExpression: public BinaryExpression {
public:
	PlusExpression(Expression *left, Expression *right);
	virtual ~PlusExpression();

	virtual double compute();
};

#endif /* PLUSEXPRESSION_HPP_ */
