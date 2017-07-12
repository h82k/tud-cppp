#ifndef PATTERNPRINTER_HPP_
#define PATTERNPRINTER_HPP_

#include "CharGenerator.hpp"

/**
 * @name PatternPrinter
 * @brief prints a diagonal pattern of characters using the CharGenerator
 * @sa CharGenerator
 * @author cppp
 */
class PatternPrinter {
public:
    /**
     * @name PatternPrinter();
     * @brief constructor of the PatternPrinter
     * @author cppp
     */
	PatternPrinter();
    /**
     * @name printPattern();
     * @brief used to actually print the pattern
     * @author cppp
     * @return void
     */
	void printPattern();			// read width and print chars in a pattern
private:
    /**
     * @name printNChars(int n);
     * @brief used to print a number of characters 
     * @param n the number of characters
     * @author cppp
     * @return void
     */
	void printNChars(int n);		// print n characters to the console
    /**
     * @name readWidth();
     * @brief reads a number input by the user
     * @author cppp
     * @return int
     */
	int readWidth();				// read width (user input)
    /**
     * @name charGenerator; 
     * @brief used to get the characters used for printNChars
     * @sa printNChars(int n);
     * @author cppp
     */
	CharGenerator charGenerator;
};

#endif /* PATTERNPRINTER_HPP_ */
