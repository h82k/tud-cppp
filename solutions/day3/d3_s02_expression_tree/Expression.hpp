#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

class Expression {
public:
	Expression();
	virtual ~Expression();
	virtual double compute() = 0;
private:
	/** forbid default copying */
	Expression(const Expression&);
};

#endif /* EXPRESSION_HPP_ */
