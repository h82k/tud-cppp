#include "Building.hpp"
#include <iostream>

int main() {
	std::cout << "Hello World" << std::endl;
	Building house(2);
	std::cout << house.toString() << std::endl;
}

