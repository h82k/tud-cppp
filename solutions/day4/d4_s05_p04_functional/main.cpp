#include <iostream>
#include <vector>
#include <string>

// for map
class Square {
	public:
		Square() {}
		int operator() (int &i) { return i*i; }
};

// for filter
class Odd {
	public:
		Odd() {}
		bool operator() (int &i) { return i%2 == 1 ? true : false ; } 
};

// for reduce
class Sum {
	public:
		Sum() {}
		int operator() ( int &i, int j ) { return i + j; }
};

template<typename InIt, typename OutIt>
OutIt map(InIt first, InIt last, OutIt out_first, Square s) {
	while(first != last) { *out_first++ = s(*first++); }
	return out_first;
}

template<typename ItType, typename OutIt>
ItType filter(ItType first, ItType last, OutIt out_first, Odd pred) {
	while(first != last) {
        if(pred(*first)) {
			*out_first++ = *first++;
		} else {
			++first;
		}
    }
	return out_first; 
}

template<typename ItType, typename T>
T reduce(ItType first, ItType last, T init, Sum s) {
	while(first != last) {
        init = s(init, *first++);
    }
    return init;
}

void print(const std::vector<int> &numbers) {
	for (auto i = numbers.begin(); i != numbers.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
	map(numbers.begin(), numbers.end(), numbers.begin(), Square()); 
	filter(numbers.begin(), numbers.end(), numbers.begin(), Odd()); 
	std::cout << reduce(numbers.begin(), numbers.end(), 0, Sum()) << std::endl;
	print(numbers);
}

std::string to_string(std::string &str, int j) { 
	return str.empty() ? std::to_string(j) : str + " - " + std::to_string(j);
}

