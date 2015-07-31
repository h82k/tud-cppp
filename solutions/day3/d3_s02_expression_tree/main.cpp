#include "NumberExpression.hpp"
#include "PlusExpression.hpp"
#include "MinusExpression.hpp"
#include <iostream>
using namespace std;

int main() {
	PlusExpression e(new MinusExpression(new NumberExpression(42), new NumberExpression(12)), new NumberExpression(10));
	cout << e.compute() << endl; // should be 40
}
