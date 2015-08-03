#include "functions.hpp"
#include <iostream>

void fun::print_star(int n) {
	while (n-- > 0) {
		std::cout << '*';
	}
	std::cout << std::endl;
}

void fun::task_b() {
	for (int i = 5; i > 1; --i) {
		print_star(i);
	}
	for (int i = 1; i <= 5; ++i) {
		print_star(i);
	}
}

void fun::task_d() {
	int width;
	do {
		std::cout << "Geben Sie die Breite ein ";
		std::cin >> width;
	} while (width < 1 || width > 75);
	
	for (int i = width; i > 1; --i) {
		print_star(i);
	}
	for (int i = 1; i <= width; ++i) {
		print_star(i);
	}
}

char fun::next_char() {
	static char c = 'z';
	if (c >= 'z') {
		c = 'a';
	}
	else {
		c++;
	}
	return c;
}

void fun::print_char(int n) {
	while (n-- > 0) {
		std::cout << next_char();
	}
	std::cout << std::endl;
}

void fun::task_e() {
	int width;
	do {
		std::cout << "Geben Sie die Breite ein ";
		std::cin >> width;
	} while (width < 1 || width > 75);
	
	for (int i = width; i > 1; --i) {
		print_char(i);
	}
	for (int i = 1; i <= width; ++i) {
		print_char(i);
	}
}
