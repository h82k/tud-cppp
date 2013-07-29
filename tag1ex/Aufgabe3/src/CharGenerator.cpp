/*
 * CharGenerator.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: jgdo
 */
#include "CharGenerator.h"

CharGenerator::CharGenerator(char initialChar) :
		nextChar(initialChar) {
}

char CharGenerator::generateNextChar() {
	char c = nextChar;
	
	if(nextChar >= 'z')
		nextChar = 'a';
	else
		nextChar++;
	
	return c;
}
