/*
 * MinusExpression.hpp
 */

#ifndef MINUSEXPRESSION_HPP_
#define MINUSEXPRESSION_HPP_

#include "BinaryExpression.hpp"

class MinusExpression: public BinaryExpression {
public:
	MinusExpression(Expression *left, Expression *right);
	virtual ~MinusExpression();
	
	virtual double compute();
private:
};

#endif /* MINUSEXPRESSION_HPP_ */
