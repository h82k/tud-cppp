#include <iostream>

void hanoi(int i, int a, int b, int c) {
	if (i > 0) {
		hanoi(i - 1, a, c, b);
		// moving a to c
		std::cout << a << " -> " << c << std::endl;
		hanoi(i - 1, b, a, c);
	}
}

int main() {
	hanoi(3, 1, 2, 3);
}
