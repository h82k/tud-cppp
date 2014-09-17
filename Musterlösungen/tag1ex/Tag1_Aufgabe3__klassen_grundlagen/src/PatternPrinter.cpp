/*
 * PatternPrinter.cpp
 */
#include <iostream>
using namespace std;

#include "PatternPrinter.h"

PatternPrinter::PatternPrinter() :
		charGenerator('k') {
}

void PatternPrinter::printNChars(int n) {
	while (n-- > 0)
		cout << charGenerator.generateNextChar();
	cout << endl;
}

int PatternPrinter::readWidth() {
	int width;
	do {
		cout << "Geben Sie die Breite ein ";
		cin >> width;
	} while (width < 1 || width > 75);
	
	return width;
}

void PatternPrinter::printPattern() {
	int width = readWidth();
	
	for (int i = width; i > 1; i--)
		printNChars(i);
	for (int i = 1; i <= width; i++)
		printNChars(i);
}
