#ifndef PATTERNPRINTER_HPP_
#define PATTERNPRINTER_HPP_

#include "CharGenerator.hpp"

class PatternPrinter {
public:
	PatternPrinter();
	void printPattern();			// read width and print chars in a pattern
private:
	void printNChars(int n);		// print n characters to the console
	int readWidth();				// read width (user input)
	CharGenerator charGenerator;
};

#endif /* PATTERNPRINTER_HPP_ */
