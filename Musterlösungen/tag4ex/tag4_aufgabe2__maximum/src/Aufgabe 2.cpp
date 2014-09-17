//============================================================================
// Name        : Aufgabe.cpp
//============================================================================

#include <iostream>
using namespace std;

template<class T>
const T& maximum(const T& t1, const T& t2) {
	return t1 > t2 ? t1 : t2;
}

class C {
public:
	C(int number) :
			number(number) {
	}
	
	bool operator>(const C& other) const {
		return number > other.number;
	}
	
	int getNumber() const {
		return number;
	}
private:
	int number;
};

ostream& operator<<(ostream& out, const C& c) {
	return out << c.getNumber();
}

int main() {
	// Aufgabe a)
	C c1(23), c2(42);
	cout << maximum(c1, c2) << endl;
	
	int i = 1;
	short s = 2;
	cout << maximum<int>(i, s) << endl;
	
	return 0;
}
