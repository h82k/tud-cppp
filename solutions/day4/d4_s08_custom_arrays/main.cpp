#include "Array.hpp"
#include <string>
#include <iostream>

template<typename T>
void printNthElement(const Array<T> &array, size_t position) {
	std::cout << array[position] << std::endl;
}

int main(int argc, char **argv) {
	Array<std::string> stringArray(10);
	stringArray[0] = "First entry";
	stringArray[1] = "Second entry";
	stringArray[9] = "Last entry";
	
	printNthElement(stringArray, 0);
	printNthElement(stringArray, 9);
	try {
		printNthElement(stringArray, 10);
	} catch (std::out_of_range &ex) {
		std::cout << "Oh oh: " << ex.what() << std::endl;
	}
	
	// Create a view of the array
	Array<std::string> arrayFromOffset1 = stringArray + 1;
	printNthElement(arrayFromOffset1, 0);
	
	try {
		printNthElement(arrayFromOffset1, 9);
	} catch (std::out_of_range &ex) {
		std::cout << "Oh oh: " << ex.what() << std::endl;
	}
	
	try {
		// Create an invalid view (offset too large) of the orignal array.
		Array<std::string> arrayFromOffset2 = stringArray + 10;
	} catch (std::out_of_range &ex) {
		std::cout << "Oh oh: " << ex.what() << std::endl;
	}
	
	// Check that accumulating offset (applying operator+ twice) works
	try {
		Array<std::string> arrayFromOffset3 = arrayFromOffset1 + 9;
	} catch (std::out_of_range &ex) {
		std::cout << "Oh oh: " << ex.what() << std::endl;
	}
	
	std::cout << "Done." << std::endl;
}
