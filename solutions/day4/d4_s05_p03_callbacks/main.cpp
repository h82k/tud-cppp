#include <iostream>

void print(int from, int to) {
	std::cout << from << " -> " << to << std::endl;
}

class C {
public:
	void operator()(int from, int to) {
		std::cout << "C: " << from << " -> " << to << std::endl;
	}
};

template<typename T>
void hanoi(int i, int a, int b, int c, T &callback) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback(a, c);
		hanoi(i - 1, b, a, c, callback);
	}
}

int main() {
	C c;
	hanoi(3, 1, 2, 3, print);
	hanoi(3, 1, 2, 3, c);
}
