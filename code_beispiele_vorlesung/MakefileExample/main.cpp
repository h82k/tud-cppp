#include <iostream>

#include "Cat.hpp"
#include "Dog.hpp"

using namespace std;

int main(void)
{
	cout << "Test" << endl;
	Dog dog;
	dog.bark();

	Cat cat;
	cat.sayMiew();
}


