#include "Array.hpp"
#include <iostream>
#include <string>

using namespace std;

template<class T>
void printNthElement(const Array<T> &array, size_t position) {
	cout << array[position] << endl;
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
	} catch (out_of_range &ex) {
		cout << "Oh oh: " << ex.what() << endl;
	}

	/*
	 * Create a view of the array
	 */
	Array<std::string> arrayFromOffset1 = stringArray + 1;
	printNthElement(arrayFromOffset1, 0);

	try {
		printNthElement(arrayFromOffset1, 9);
	} catch (out_of_range &ex) {
		cout << "Oh oh: " << ex.what() << endl;
	}

	try {
		// Create an invalid view (offset too large) of the orignal array.
		Array<string> arrayFromOffset2 = stringArray + 10;
	} catch (out_of_range &ex) {
		cout << "Oh oh: " << ex.what() << endl;
	}

	// Check that accumulating offset (applying operator+ twice) works
	try {
		Array<string> arrayFromOffset3 = arrayFromOffset1 + 9;
	} catch (out_of_range &ex) {
		cout << "Oh oh: " << ex.what() << endl;
	}
	return 0;
}
