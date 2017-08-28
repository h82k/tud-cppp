#include <iostream>
#include <vector>

// function pointer
void tripple(int & x) {
	x *= 3;
}

// functor
class Multiplier {
public:
	Multiplier(int factor):factor(factor) {}
	void operator() (int & i) {i *= factor;}
private:
	int factor;
};

// apply function pointer or functor
//template<typename InputIterator, typename ValueType>
//void(*callback)(ValueType i)
template<typename InputIterator, typename F>
void applyMultiplicator(InputIterator begin, InputIterator end, F callback) {
	for(auto i = begin; i != end; ++i) {
		callback(*i);
	}
}

// apply method function
/*template<typename InputIterator, typename ValueType, typename ClassT>
void applyMultiplicator(InputIterator begin, InputIterator end, void(ClassT::*callback)(ValueType i), ClassT * c) {
	for(auto i = begin; i != end; ++i) {
		(c->*callback)(*i);
	}
}*/

void print(const std::vector<int> & numbers) {
	for (auto i = numbers.begin(); i != numbers.end(); ++i) {
		std::cout << *i << ", ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> numbers = {1, 3, 59, 24, 14, 50, 23, 56, 95, 45};
	print(numbers);
	applyMultiplicator(numbers.begin(), numbers.end(), tripple);
	print(numbers);
	Multiplier mul(2);
	applyMultiplicator(numbers.begin(), numbers.end(), mul);
	print(numbers);
	int c = 10;
	auto lambda = [&](int & i){i *= c;};
	applyMultiplicator(numbers.begin(), numbers.end(), lambda);
	print(numbers);
	
	c = 4;
	applyMultiplicator(numbers.begin(), numbers.end(), lambda);
	print(numbers);
}
