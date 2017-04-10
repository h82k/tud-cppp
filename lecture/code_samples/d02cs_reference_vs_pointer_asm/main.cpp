/**
 * This program shows how references and pointers are treated on the assembler code level.
 * Build the project and open Debug/main.o . The assembler code related to the main function
 * can be found at label "LBB2".
 */

#include <iostream>

void printRef(int &value) {
	std::cout << value << std::endl;
}

void print(int value) {
	std::cout << value << std::endl;
}

void printPointer(int *value) {
	std::cout << value << std::endl;
}

int main() {
	int i = 1;
	print(i);
	printRef(i);
	printPointer(&i);
}
