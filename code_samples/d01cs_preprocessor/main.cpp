#define DEBUG

#include "debug.hpp"
#include <iostream>


int main() {
	std::cout << "Regular output..." << std::endl;
	int i;
	LOG("Some debug output [i=" << i << "]")
	std::cout << "Bye bye." << std::endl;
}
