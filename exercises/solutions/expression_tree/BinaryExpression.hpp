#ifndef BINARYEXPRESSION_HPP_
#define BINARYEXPRESSION_HPP_

#include "Expression.hpp"

/**
 * @name BinaryExpression
 * @author cppp
 * @brief class describing a mathematical binary expression using the inherit expression
 * @sa Expression
 */
class BinaryExpression: public Expression {
public:
    /**
     * @name BinaryExpression(Expression *left, Expression *right);
     * @author cppp
     * @brief constructor initialized with two expressions, one left, one right
     * @param left the lefthand expression
     * @param right the righthand expression
     */
	BinaryExpression(Expression *left, Expression *right);
    /**
     * @name ~BinaryExpression();
     * @author cppp
     * @brief destructor of binary expression
     */
	virtual ~BinaryExpression();
protected:
	Expression *left, *right;
};

#endif /* BINARYEXPRESSION_HPP_ */
