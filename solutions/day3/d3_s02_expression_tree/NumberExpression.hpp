#ifndef NUMBEREXPRESSION_HPP_
#define NUMBEREXPRESSION_HPP_

#include "Expression.hpp"

/**
 * @name NumberExpression
 * @author cppp
 * @brief serves as leaf of an expression tree storing a number
 * @sa Expression
 */
class NumberExpression: public Expression {
public:
    /**
     * @name NumberExpression(double n);
     * @author cppp
     * @brief constructor with initial number
     * @param n the stored number
     */
	NumberExpression(double n);
    /**
     * @name ~NumberExpression();
     * @author cppp
     * @brief destructor of the number expression
     */
	virtual ~NumberExpression();
    /**
     * @name compute();
     * @author cppp
     * @brief returns the number attribute
     * @return this->number
     */
	virtual double compute();
private:
	double number;
};

#endif /* NUMBEREXPRESSION_HPP_ */
