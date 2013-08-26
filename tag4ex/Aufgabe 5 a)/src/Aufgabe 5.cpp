//============================================================================
// Name        : Aufgabe.cpp
//============================================================================

#include <iostream>
using namespace std;

void hanoi(int i, int a, int b, int c) {
	if (i > 0) {
		hanoi(i - 1, a, c, b);
		// moving a to c
		cout << a << " -> " << c << endl;
		hanoi(i - 1, b, a, c);
	}
}

int main() {
	hanoi(3, 1, 2, 3);
	return 0;
}
