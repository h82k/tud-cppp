#include <iostream>
using namespace std;

void hanoi(int i, int a, int b, int c, void(*callback)(int from, int to)) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback(a, c);
		hanoi(i - 1, b, a, c, callback);
	}
}

void print(int from, int to) {
	cout << from << " -> " << to << endl;
}

int main() {
	hanoi(3, 1, 2, 3, print);
}
