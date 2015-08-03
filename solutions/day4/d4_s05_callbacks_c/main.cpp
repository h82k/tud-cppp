#include <iostream>
using namespace std;

void print(int from, int to) {
	cout << from << " -> " << to << endl;
}

class C {
public:
	void operator()(int from, int to) {
		cout << "C: " << from << " -> " << to << endl;
	}
};

template<class T>
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
