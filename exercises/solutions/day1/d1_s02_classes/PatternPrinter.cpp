#include "PatternPrinter.hpp"
#include <iostream>

PatternPrinter::PatternPrinter():
	charGenerator('k')
{}

void PatternPrinter::printNChars(int n) {
	while (n-- > 0) {
		std::cout << charGenerator.generateNextChar();
	}
	std::cout << std::endl;
}

int PatternPrinter::readWidth() {
	int width;
	do {
		std::cout << "Geben Sie die Breite ein ";
		std::cin >> width;
	} while (width < 1 || width > 75);
	return width;
}

void PatternPrinter::printPattern() {
	int width = readWidth();
	for (int i = width; i > 1; --i) {
		printNChars(i);
	}
	for (int i = 1; i <= width; ++i) {
		printNChars(i);
	}
}
