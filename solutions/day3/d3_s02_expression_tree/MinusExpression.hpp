#ifndef MINUSEXPRESSION_HPP_
#define MINUSEXPRESSION_HPP_

#include "BinaryExpression.hpp"

/**
 * @name MinusExpression
 * @author cppp
 * @brief used to express a binary minus expression
 * @sa BinaryExpression
 * @sa Expression
 */
class MinusExpression: public BinaryExpression {
public:
    /**
     * @name MinusExpression(Expression *left, Expression *right);
     * @author cppp
     * @brief constructor of a minus expression using a left and right expression as pointer
     * @param left the lefthand expression
     * @param right the righthand expression
     */
	MinusExpression(Expression *left, Expression *right);
    /**
     * @name ~MinusExpression();
     * @author cppp
     * @brief destructor of the minus expression object
     */
	virtual ~MinusExpression();
    /**
     * @name compute();
     * @author cppp
     * @brief retuns the result of the righthand expression minus the lefthand one
     * @param the result of the substraction
     */
	virtual double compute();
private:
};

#endif /* MINUSEXPRESSION_HPP_ */
