#include <iostream>

class C {
public:
	explicit C(int i) :myInt(i) {}

	const int myInt;
};

void myFunction(C c) {
	std::cout << "c.myInt: " << c.myInt << std::endl;
}

int main() {

	myFunction(3);

	return 0;
}
