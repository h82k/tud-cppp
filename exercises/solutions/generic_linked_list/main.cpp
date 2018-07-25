#include "List.hpp"
#include <iostream>

int main() {
	List<List<int> > list; // Prior to C++11: >> is an operator, so > > is required for nested templates. C++11 and later: >> is also valid
	list.appendElement(List<int>());
	list.getFirst().appendElement(1);
	list.getFirst().appendElement(2);
	list.appendElement(List<int>());
	list.getLast().appendElement(3);
	list.appendElement(List<int>());
	list.getLast().appendElement(4);
	list.getLast().appendElement(5);
	std::cout << list << std::endl;
}
