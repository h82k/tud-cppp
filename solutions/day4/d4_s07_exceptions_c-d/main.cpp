#include "List.hpp"
#include <iostream>

int main() {
	List<int> list;
	list.appendElement(0);
	list.appendElement(1);
	list.appendElement(2);
	
	try {
		std::cout << list.getNthElement(2) << std::endl; // should work
		std::cout << list.getNthElement(3) << std::endl; // should not work
		std::cout << "error!" << std::endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	try {
		list.insertElementAt(3, 3); // should work
		std::cout << "element at 3 inserted" << std::endl;
		list.insertElementAt(5, 5); // should not work
		std::cout << "error!" << std::endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	try {
		list.deleteAt(2); // should work
		std::cout << "element at 2 deleted" << std::endl;
		list.deleteAt(3); // should not work
		std::cout << "error!" << std::endl; // should never be reached
	} catch (const std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	
	std::cout << list << std::endl; // should be [0, 1, 3]
}
