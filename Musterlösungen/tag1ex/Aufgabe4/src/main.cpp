/*
 * main.cpp
 */

#include <iostream>
#include "Vector3.h"

using namespace std;

void foo(Vector3 v) {
	cout << "foo begin" << endl;
	cout << v << endl;
	cout << "foo end" << endl;
}

int main() {
	Vector3 v = Vector3(1, 2, 3) + Vector3(4, 5, 6) - Vector3(7, 8, 9);
	cout << v << endl; // should be (-2, -1, 0)
	
	foo(v);
	
	cout << (Vector3() + Vector3(4, 3, 1)) * Vector3(5, 7, 1) << endl; // should be 42
	        
	return 0;
}

