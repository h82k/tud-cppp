#include "Callback.hpp"
#include <iostream>
#include <utility>

typedef pair<int, int> intpair;

class C {
public:
	C() {}
	C(const C&) {
		std::cout << "copying C" << std::endl;
	}
	
	void print(intpair p) {
		std::cout << "C::print(): " << p.first << " -> " << p.second << std::endl;
	}
	void operator()(intpair p) {
		std::cout << "C::(): " << p.first << " -> " << p.second << std::endl;
	}
};

void print(intpair p) {
	std::cout << p.first << " -> " << p.second << std::endl;
}

void hanoi(int i, int a, int b, int c, Callback<intpair> &callback) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback(intpair(a, c));
		hanoi(i - 1, b, a, c, callback);
	}
}

int main() {
	C c;
	Callback<std::pair<int, int> > functionCallback = Callback<intpair>(print);
	hanoi(3, 1, 2, 3, functionCallback);
	
	Callback<std::pair<int, int> > functorCallback = Callback<intpair>(c);
	hanoi(3, 1, 2, 3, functorCallback);
	
	Callback<std::pair<int, int> > methodCallback = Callback<intpair>(&C::print, &c);
	hanoi(3, 1, 2, 3, methodCallback);
}
