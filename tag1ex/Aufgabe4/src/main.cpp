/*
 * main.cpp
 */

#include <iostream>
#include "Vector3.h"

using namespace std;

int main() {
	cout <<  Vector3(1, 2, 3) + Vector3(4, 5, 6) - Vector3(7, 8, 9)  << endl; // should be (-2, -1, 0)
	cout << (Vector3() + Vector3(4, 3, 1)) * Vector3(5, 7, 1)  << endl; // should be 42
	
	return 0;
}

