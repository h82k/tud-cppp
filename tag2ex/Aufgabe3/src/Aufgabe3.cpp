//============================================================================
// Name        : Aufgabe3.cpp
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
	
	List list2(list);
	
	list.deleteFirst();
	list.deleteFirst();
	
	for (ListIterator iter = list.begin(); iter != list.end(); iter++) {
		cout << *iter << endl;
	}

	for (ListIterator iter = list2.begin(); iter != list2.end(); iter++) {
		cout << *iter << endl;
	}
	
	return 0;
}
