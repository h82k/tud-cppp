class PatternPrinter {
public:
	PatternPrinter();
	void printPattern();			// read width and print chars in a pattern
private:
	CharGenerator charGen;
	void printNChars(int n);	// print n characters to the console
	int readWidth();				// read width (user input)
};
