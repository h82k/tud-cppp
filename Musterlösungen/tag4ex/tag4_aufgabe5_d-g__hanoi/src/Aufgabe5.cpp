//============================================================================
// Name        : Aufgabe5.cpp
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

#include "Callback.hpp"

void print(pair<int, int> p) {
	cout << p.first << " -> " << p.second << endl;
}

class C {
public:
	C() {
	}
	
	C(const C&) {
		cout << "copying C" << endl;
	}
	
	void print(pair<int, int> p) {
		cout << "C::print(): " << p.first << " -> " << p.second << endl;
	}
	
	void operator()(pair<int, int> p) {
		cout << "C::(): " << p.first << " -> " << p.second << endl;
	}
};

void hanoi(int i, int a, int b, int c, CallbackBase<pair<int, int> > *callback) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback->call(pair<int, int>(a, c));
		hanoi(i - 1, b, a, c, callback);
	}
}

int main() {
	// function callback
	FunctionCallback<pair<int, int> > cb1(print);
	hanoi(3, 1, 2, 3, &cb1);
	
	// functor callback
	C c;
	FunctorCallback<pair<int, int> , C> cb2(c);
	hanoi(3, 1, 2, 3, &cb2);
	
	// method callback
	MethodCallback<pair<int, int> , C> cb3(&C::print, &c);
	hanoi(3, 1, 2, 3, &cb3);
	return 0;
}
