/*
 * functions.cpp
 */
#include "functions.hpp"

#include <iostream>
using namespace std;

void print_star(int n) {
	while (n-- > 0)
		cout << '*';
	cout << endl;
}

void task_b() {
	for (int i = 5; i > 1; i--)
		print_star(i);
	for (int i = 1; i <= 5; i++)
		print_star(i);
}

void task_d() {
	int width;
	do {
		cout << "Geben Sie die Breite ein ";
		cin >> width;
	} while (width < 1 || width > 75);

	for (int i = width; i > 1; i--)
		print_star(i);
	for (int i = 1; i <= width; i++)
		print_star(i);
}

char next_char() {
	static char c = 'z';
	
	if (c >= 'z')
		c = 'a';
	else
		c++;
	return c;
}

void print_char(int n) {
	while (n-- > 0)
		cout << next_char();
	cout << endl;
}

void task_e() {
	int width;
	do {
		cout << "Geben Sie die Breite ein ";
		cin >> width;
	} while (width < 1 || width > 75);

	for (int i = width; i > 1; i--)
		print_char(i);
	for (int i = 1; i <= width; i++)
		print_char(i);
}
