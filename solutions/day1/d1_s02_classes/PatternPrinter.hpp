#ifndef PATTERNPRINTER_HPP_
#define PATTERNPRINTER_HPP_

#include "CharGenerator.hpp"

class PatternPrinter {
public:
	PatternPrinter();
	void printPattern();
private:
	void printNChars(int n);
	int readWidth();
	CharGenerator charGenerator;
};

#endif /* PATTERNPRINTER_HPP_ */
