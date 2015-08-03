#include "List.hpp"
#include <iostream>
using namespace std;

int main() {
	List<List<int> > list; //  >> is an operator, so use > > for nested templates
	list.appendElement(List<int>());
	list.getFirst().appendElement(1);
	list.getFirst().appendElement(2);
	list.appendElement(List<int>());
	list.getLast().appendElement(3);
	list.appendElement(List<int>());
	list.getLast().appendElement(4);
	list.getLast().appendElement(5);
	cout << list << endl;
}
