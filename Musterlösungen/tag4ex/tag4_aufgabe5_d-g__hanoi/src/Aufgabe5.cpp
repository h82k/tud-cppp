//============================================================================
// Name        : Aufgabe5.cpp
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

#include "Callback.hpp"

typedef pair<int, int> intpair;

void print(intpair p) {
	cout << p.first << " -> " << p.second << endl;
}

class C {
public:
	C() {
	}
	
	C(const C&) {
		cout << "copying C" << endl;
	}
	
	void print(intpair p) {
		cout << "C::print(): " << p.first << " -> " << p.second << endl;
	}
	
	void operator()(intpair p) {
		cout << "C::(): " << p.first << " -> " << p.second << endl;
	}
};

void hanoi(int i, int a, int b, int c, CallbackBase<intpair> &callback) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback.call(intpair(a, c));
		hanoi(i - 1, b, a, c, callback);
	}
}

int main() {
	// function callback
	FunctionCallback<intpair > cb1(print);
	hanoi(3, 1, 2, 3, cb1);
	
	// functor callback
	C c;
	FunctorCallback<intpair , C> cb2(c);
	hanoi(3, 1, 2, 3, cb2);
	
	// method callback
	MethodCallback<intpair , C> cb3(&C::print, &c);
	hanoi(3, 1, 2, 3, cb3);
	return 0;
}
