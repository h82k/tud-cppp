#ifndef PLUSEXPRESSION_HPP_
#define PLUSEXPRESSION_HPP_

#include "BinaryExpression.hpp"

/**
 * @name PlusExpression
 * @author cppp
 * @brief describes a binary plus expression
 */
class PlusExpression: public BinaryExpression {
public:
    /**
     * @name PlusExpression(Expression *left, Expression *right);
     * @author cppp
     * @brief constructor of a binary plus expression
     * @param left the lefthand side expression
     * @param right the righthand side expression
     */
	PlusExpression(Expression *left, Expression *right);
    /**
     * @name ~PlusExpression();
     * @author cppp
     * @brief destructor of the plus expression object
     */
	virtual ~PlusExpression();
    /**
     * @name compute();
     * @author cppp
     * @brief returns the addition of lefthand side plus righthand side 
     * @return the result
     */
	virtual double compute();
};

#endif /* PLUSEXPRESSION_HPP_ */
