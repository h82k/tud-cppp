#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

template<class T>
void print(const T& t) {
	std::cout << "[";
	std::copy(t.begin(), t.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "]" << std::endl;
}

bool pred(int i) {
	return i >= 4;
}

int main() {
	// b)
	int numbers[] = { 1, 2, 3, 4, 5 };
	std::vector<int> vec(numbers, numbers + 5);
	print(vec);
	
	// c)
	std::list<int> lst(vec.begin() + 1, vec.begin() + 4);
	print(lst);
	
	// d)
	lst.insert(lst.begin(), vec.begin() + 4, vec.begin() + 5);
	print(lst);
	
	// e)
	vec.clear();
	print(vec);
	
	// f) 
	std::remove_copy_if(lst.begin(), lst.end(), back_inserter(vec), pred);
	print(vec);
}
