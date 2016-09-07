#include <iostream>
#include <vector>
#include <string>

// for map
class Square {
	public:
		Square(int i):i(i) {}
		int operator()(){ return i*i; }
	private:
		int i;
};

// for filter
class Odd {
	public:
		Odd(int i):i(i) {}
		bool operator()() { return i%2 == 1 ? true : false ; } 
	private:
		int i;
};

// for reduce
class Sum {
	public:
		Sum(int &i, int j): i(i), j(j) {}
		int operator()() { return i + j; }
	private:
		int i, j;
};

std::string to_string(std::string &str, int j) { 
	return str.empty() ? std::to_string(j) : str + " - " + std::to_string(j);
}

template<typename InIt, typename OutIt>
OutIt map(InIt first, InIt last, OutIt out_first, Square s) {
	while(first != last) {
        *out_first++ = func(*first++);
    }
	return out_first;
}

template<typename ItType, typename OutIt>
ItType filter(ItType first, ItType last, OutIt out_first, Odd o) {
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

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

	std::cout 	<< "Filter:\t[ "
				<< reduce(numbers.begin(), numbers.end(), std::string {}, to_string)
				<< " ]" << std::endl;

}
