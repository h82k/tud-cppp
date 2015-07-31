#include "CharGenerator.hpp"

CharGenerator::CharGenerator(char initialChar):
	nextChar(initialChar)
{}

char CharGenerator::generateNextChar() {
	char c = nextChar;
	if(nextChar >= 'z') {
		nextChar = 'a';
	}
	else {
		nextChar++;
	}
	return c;
}
