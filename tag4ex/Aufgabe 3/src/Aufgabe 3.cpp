//============================================================================
// Name        : Aufgabe.cpp
//============================================================================

#include <iostream>
using namespace std;

#include "Vector3.h"

int main() {
	cout << Vector3<int>(1, 2, 3) / 5 << endl; // should be (0, 0, 0)
	cout << Vector3<double>(1, 2, 3) / 5 << endl; // should be (0.2, 0.4, 0.6)
	        
	return 0;
}
