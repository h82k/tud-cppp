//============================================================================
// Name        : Aufgabe6.cpp
//============================================================================

#include <iostream>
using namespace std;

/** Class for showing exception effects */
class C {
public:
	C() {
		cout << "C" << endl;
	}
	
	~C() {
		cout << "~C" << endl;
	}
	
	C(const C& other) {
		cout << "copy C" << endl;
	}
};

int main() {
	try {
		throw C();
	} catch (const C& c) {
		cout << "catch C&" << endl;
	} catch (C c) {
		cout << "catch C" << endl;
	}

	cout << "end" << endl;
	return 0;
}
