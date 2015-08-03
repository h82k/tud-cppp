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

int main() {
	try {
		throw C();
	} catch (const C& c) {
		std::cout << "catch C&" << std::endl;
	} catch (C c) {
		std::cout << "catch C" << std::endl;
	}
	std::cout << "end" << std::endl;
}
