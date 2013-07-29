/*
 * CharGenerator.h
 *
 *  Created on: Jul 29, 2013
 *      Author: jgdo
 */

#ifndef CHARGENERATOR_H_
#define CHARGENERATOR_H_


class CharGenerator {
public:
	CharGenerator(char initialChar = 'a');
	
	char generateNextChar();
private:
	char nextChar;
};

#endif /* CHARGENERATOR_H_ */
