/*
 * Expression.h
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

class Expression {
public:
	Expression();
	virtual ~Expression();
	virtual double compute() = 0;

private:
	/** forbid default copying */
	Expression(const Expression&);
};

#endif /* EXPRESSION_H_ */
