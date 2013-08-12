//============================================================================
// Name        : Aufgabe3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "List.h"

int main() {
	
	List list;
	list.appendElement(1);
	list.appendElement(2);
	list.appendElement(3);
	list.prependElement(0);
	
	for (int i = 0; i < list.getSize(); i++) {
		cout << list.getNthElement(i) << endl;
	}

	for (ListIterator iter = list.begin(); iter != list.end(); iter++) {
		cout << *iter << endl;
	}
	
	return 0;
}
