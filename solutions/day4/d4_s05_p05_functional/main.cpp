#include <iostream>
#include <vector>
#include <string>

// for map
int square(int i) { return i*i; }

// for filter
bool is_odd(int i) { return i%2 == 1 ? true : false ; }

// for reduce
int sum(int &i, int j) { return i + j; }
std::string to_string(std::string &str, int j) { 
	return str.empty() ? std::to_string(j) : str + " - " + std::to_string(j);
}

// for map
class Square {
	public:
		Square() {}
		int operator() (int i) { return i*i; }
};

// for filter
class Odd {
	public:
		Odd() {}
		bool operator() (int i) { return i%2 == 1 ? true : false ; } 
};

// for reduce
class Sum {
	public:
		Sum() {}
		int operator() ( int i, int j ) { return i + j; }
};

template<typename InIt, typename OutIt, typename FuncType>
OutIt map(InIt first, InIt last, OutIt out_first, FuncType func) {
	while(first != last) { *out_first++ = func(*first++); }
	return out_first;
}

template<typename ItType, typename OutIt, typename FuncType>
ItType filter(ItType first, ItType last, OutIt out_first, FuncType pred) {
	while(first != last) {
        if(pred(*first)) {
			*out_first++ = *first++;
		} else {
			++first;
		}
    }
	return out_first; 
}

template<typename ItType, typename T, typename FuncType>
T reduce(ItType first, ItType last, T init, FuncType func) {
	while(first != last) {
        init = func(init, *first++);
    }
    return init;
}

void functionpointer() {
	std::cout	<< "Function Pointer:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};

	std::cout 	<< "Init:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	map(numbers.begin(), numbers.end(), numbers.begin(), square);

	std::cout 	<< "Map:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	filter(numbers.begin(), numbers.end(), numbers.begin(), is_odd);

	std::cout 	<< "Filter:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	std::cout 	<< "Reduce:\t"
				<< reduce(numbers.begin(), numbers.end(), 0, sum) << std::endl;
}

void functors() {
	std::cout	<< "Functors:" << std::endl;
  std::vector<int> numbers = {1, 2, 3, 4, 5};

	std::cout 	<< "Init:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	map(numbers.begin(), numbers.end(), numbers.begin(), Square());

	std::cout 	<< "Map:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	filter(numbers.begin(), numbers.end(), numbers.begin(), Odd());

	std::cout 	<< "Filter:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

	std::cout 	<< "Reduce:\t"
				<< reduce(numbers.begin(), numbers.end(), 0, Sum()) << std::endl;
}

int main() {
	functionpointer();
	std::cout << std::string(40, '-') << std::endl;
	functors();
}
