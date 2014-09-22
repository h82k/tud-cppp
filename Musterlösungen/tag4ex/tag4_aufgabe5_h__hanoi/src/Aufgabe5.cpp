//============================================================================
// Name        : Aufgabe5.cpp
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

#include "Callback.hpp"

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

void print(pair<int, int> p) {
	cout << p.first << " -> " << p.second << endl;
}

void hanoi(int i, int a, int b, int c, Callback<pair<int, int> > callback) {
	if (i > 0) {
		hanoi(i - 1, a, c, b, callback);
		// moving a to c
		callback(pair<int, int>(a, c));
		hanoi(i - 1, b, a, c, callback);
	}
}

int main() {
	C c;
	
	hanoi(3, 1, 2, 3, Callback<pair<int, int> >(print)); // function callback
	hanoi(3, 1, 2, 3, Callback<pair<int, int> >(c)); // functor callback
	hanoi(3, 1, 2, 3, Callback<pair<int, int> >(&C::print, &c)); // method callback
	return 0;
}
