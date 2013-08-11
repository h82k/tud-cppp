//============================================================================
// Name        : Ausgabe1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void foo(int& i) {
	int i2 = i;
	int& i3 = i;
	
	cout << "i = " << i << endl;
	cout << "i2 = " << i2 << endl;
	cout << "i3 = " << i3 << endl;
	cout << "&i = " << &i << endl;
	cout << "&i2 = " << &i2 << endl;
	cout << "&i3 = " << &i3 << endl;
}

int main() {
	int var = 42;
	cout << "&var = " << &var << endl;
	foo(var);
	
	return 0;
}

