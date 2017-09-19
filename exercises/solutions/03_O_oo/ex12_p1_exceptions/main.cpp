#include <iostream>

/** Class for showing exception effects */
class C {
public:
	C() {
		std::cout << "C" << std::endl;
	}
	
	~C() {
		std::cout << "~C" << std::endl;
	}
	
	C(const C& other) {
		std::cout << "copy C" << std::endl;
	}
};

/*
 * Note: If both catch blocks are used, the compiler will issue a warning because
 * the first catch block 'hides' the second one
 */
int main() {
	try {
		throw C();
	// either use catch by reference ...
	} catch (const C& c) {
		std::cout << "catch C&" << std::endl;
	// ... or catch by value
	} catch (C c) {
		std::cout << "catch C" << std::endl;
	}
	std::cout << "end" << std::endl;
}
