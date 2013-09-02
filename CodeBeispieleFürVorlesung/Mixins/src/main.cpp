#include <iostream>
#include<vector>

#include "System.h"

#include "ConsoleLogger.h"
#include "PasswordSecurity.h"
#include "MacOSX.h"
#include "Enterprise.h"

using namespace std;

int _main(int argc, char **argv) {
	System<ConsoleLogger, PasswordSecurity, MacOSX, Enterprise> system;
	system.print("Yihaa!");
	cout << "Password accepted: " << system.checkPassword("*****") << endl;

	return 0;
}

template<class F, class T>
void applyToSequence(F function, T* begin, T* end){
	while (begin != end) function(*begin++);
}

template<class S>
void print(const S& s){
	cout << ":::>  " << s;
	cout << endl;
}

void validateAges(int a){
	if(a > 100 || a < 0){
		cout << a << " is not a valid age!" << endl;
	}
}

int main(int argc, char **argv) {
	void (*fp1)(const string&) = print<string>;
	void (*fp2)(int) = validateAges;

	fp1("foo");
	fp2(500);

	void (ConsoleLogger::*fp3)(const string&) const = &ConsoleLogger::print;
	ConsoleLogger logger;
	(logger.*fp3)("bar");

	int n[] = {-1, 20, 33, 120};
	applyToSequence(ConsoleLogger(), n, n + 4);
	applyToSequence(print<int>, n, n + 4);
	applyToSequence(validateAges, n, n + 4);
}

