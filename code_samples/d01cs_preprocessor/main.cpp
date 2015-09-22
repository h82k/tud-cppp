#define DEBUG

#include "debug.hpp"
#include <iostream>


int main() {
	std::cout << "Regular output..." << std::endl;
	int i = 1;
	LOG("Some debug output [i=" << i << "]")
	i++;
	std::cout << "Bye bye." << std::endl;
}
