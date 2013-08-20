//============================================================================
// Name        : Aufgabe.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "NumberExpression.h"
#include "PlusExpression.h"
#include "MinusExpression.h"


int main() {
	PlusExpression e(new MinusExpression(new NumberExpression(42), new NumberExpression(12)), new NumberExpression(10));
	
	cout << e.compute() << endl; // should be 40
	
	return 0;
}
