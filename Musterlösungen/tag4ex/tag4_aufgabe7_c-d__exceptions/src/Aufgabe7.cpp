//============================================================================
// Name        : Aufgabe7.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "List.h"

int main() {
	
	List<int> list;
	
	list.appendElement(0);
	list.appendElement(1);
	list.appendElement(2);
	
	try {
		cout << list.getNthElement(2) << endl; // should work
		cout << list.getNthElement(3) << endl; // should not work
		cout << "error!" << endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		cout << ex.what() << endl;
	}

	try {
		list.insertElementAt(3, 3); // should work
		cout << "element at 3 inserted" << endl;
		list.insertElementAt(5, 5); // should not work
		cout << "error!" << endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		cout << ex.what() << endl;
	}

	try {
		list.deleteAt(2); // should work
		cout << "element at 2 deleted" << endl;
		list.deleteAt(3); // should not work
		cout << "error!" << endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		cout << ex.what() << endl;
	}

	cout << list << endl; // should be [0, 1, 3]
	
	return 0;
}
