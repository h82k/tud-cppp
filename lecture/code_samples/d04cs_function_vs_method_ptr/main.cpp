#include <iostream>

using std::cout;
using std::endl;

class C {
public:
	template<class S>
	void print(const S& s) {
		cout << ":::>  " << s << endl;
	}

	void validateAges(int a) {
		if (a > 100 || a < 0) {
			cout << a << " is not a valid age!" << endl;
		}
	}
};

template<class S>
void print(const S& s) {
	cout << ":::>  " << s << endl;
}

void validateAges(int a) {
	if (a > 100 || a < 0) {
		cout << a << " is not a valid age!" << endl;
	}
}

template<class F, class T>
void applyToSequence(F function, T* begin, T* end) {
	while (begin != end)
		function(*begin++);
}

template<class C, class F, class T>
void applyToSequence(C object, F method, T* begin, T* end) {
	while (begin != end)
		(object.*method)(*begin++);
}

int main() {
	int n[] = { -1, 20, 33, 120 };
	applyToSequence(print<int>, n, n + 4);
	applyToSequence(validateAges, n, n + 4);

	applyToSequence(C(), &C::print<int>, n, n + 4);
	applyToSequence(C(), &C::validateAges, n, n + 4);
}

