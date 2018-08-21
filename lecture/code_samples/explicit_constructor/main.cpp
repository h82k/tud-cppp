#include <iostream>

/**
 * This example shows that C++ may perform implicit type conversion (in this case: int --> C).
 *
 * To disallow implicit conversion, place 'explicit' in front of the respective constructor.
 */
class C {
public:
	C(int i) :myInt(i) {}

	const int myInt;
};

void myFunction(C c) {
	std::cout << "c.myInt: " << c.myInt << std::endl;
}

int main() {

	myFunction(3);

	return 0;
}
