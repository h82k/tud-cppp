/*
 * PatternPrinter.h
 */

#ifndef PATTERNPRINTER_H_
#define PATTERNPRINTER_H_

#include "CharGenerator.h"

class PatternPrinter {
public:
	PatternPrinter();
	
	void printNChars(int n);
	
	int readWidth();
	
	void printPattern();
private:
	CharGenerator charGenerator;
};

#endif /* PATTERNPRINTER_H_ */
