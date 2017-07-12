#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

/**
 * @name Expression
 * @author cppp
 * @brief expression class used to inherit from
 * @sa BinaryExpression
 * @sa NumberExpression
 */
class Expression {
public:
    /**
     * @name Expression();
     * @author cppp
     * @brief constructor just printing create msg
     */
	Expression();
    /**
     * @name ~Expression();
     * @author cppp
     * @brief destructor just printing delete msg
     */
	virtual ~Expression();
    /**
     * @name compute();
     * @author cppp
     * @brief pure virtual compute function
     */
	virtual double compute() = 0;
private:
	/** forbid default copying */
	Expression(const Expression&);
};

#endif /* EXPRESSION_HPP_ */
