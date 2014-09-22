/*
 * PatternPrinter.hpp
 */

#ifndef PATTERNPRINTER_HPP_
#define PATTERNPRINTER_HPP_

#include "CharGenerator.hpp"

class PatternPrinter {
public:
	PatternPrinter();
	
	void printNChars(int n);
	
	int readWidth();
	
	void printPattern();
private:
	CharGenerator charGenerator;
};

#endif /* PATTERNPRINTER_HPP_ */
