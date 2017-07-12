#ifndef CHARGENERATOR_HPP_
#define CHARGENERATOR_HPP_

/**
 * @name CharGenerator
 * @brief A generator for characters.
 * @author cppp
 * Char generator which can be used to incrementally create characters.
 */
class CharGenerator {
public:
    /**
     * @name CharGenerator(char initialChar = 'a');
     * @brief Constructor for CharGenerator
     * @author cppp
     * @param initialChar sets the character to be started with.
     */
	CharGenerator(char initialChar = 'a');
    /**
     * @name generateNextChar();
     * @brief returns the next character and increments the stored by one.
     * @author cppp
     * @return char the next character
     */
	char generateNextChar();
private:
    /**
     * @name nextChar;
     * @brief stores the next character.
     * @author cppp
     */
	char nextChar;
};

#endif /* CHARGENERATOR_HPP_ */
