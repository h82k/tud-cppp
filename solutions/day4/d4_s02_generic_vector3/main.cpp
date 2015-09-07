#include "Vector3.hpp"
#include <iostream>

int main() {
	std::cout << Vector3<int>(1, 2, 3) / 5 << std::endl; // should be (0, 0, 0)
	std::cout << Vector3<double>(1, 2, 3) / 5 << std::endl; // should be (0.2, 0.4, 0.6)
}
