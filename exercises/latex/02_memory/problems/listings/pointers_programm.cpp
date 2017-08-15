#include <iostream>

void foo(int &i) {
	int i2 = i;
	int &i3 = i;
	
	std::cout << "i = " << i << std::endl;
	std::cout << "i2 = " << i2 << std::endl;
	std::cout << "i3 = " << i3 << std::endl;
	std::cout << "&i = " << &i << std::endl;
	std::cout << "&i2 = " << &i2 << std::endl;
	std::cout << "&i3 = " << &i3 << std::endl;
}

int main() {
	int var = 42;
	std::cout << "&var = " << &var << std::endl;
	foo(var);
}
