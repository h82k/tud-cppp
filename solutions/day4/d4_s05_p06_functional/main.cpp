#include <iostream>
#include <vector>
#include <string>
#include <cmath> // for std::sin, std::asin
#include <iomanip> // for advanced output formatting, e.g., std::setw, std::left

////////////////////////////////////////////////////////////////////////////////
// Exercise 5.2 map, filter, reduce
////////////////////////////////////////////////////////////////////////////////

template<typename InIt, typename OutIt>
OutIt map_funcpointer(InIt first, InIt last, 
		OutIt out_first, double(*func)(double i)) {
	while(first != last) {
        *out_first++ = func(*first++);
    }
	return out_first;
}

template<typename ItType, typename OutIt>
ItType filter_funcpointer(ItType first, ItType last, 
		OutIt out_first, bool(*pred)(int i)) {
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
T reduce_funcpointer(ItType first, ItType last, T init, T(*func)(T i, double j)) {
	while(first != last) {
        init = func(init, *first++);
    }
    return init;
}

////////////////////////////////////////////////////////////////////////////////
// Exercise 5.3 Functions used as functionpointers
////////////////////////////////////////////////////////////////////////////////

// for map
double square(double i) { return i * i; }

// for filter
bool is_odd(int i) { return i % 2 == 1 ? true : false; }

// for reduce
double sum(double i, double j) { return i + j; }

template <class T> 
std::string to_string(std::string str, const T j) {
	return str.empty() ? std::to_string(j) : str + " - " + std::to_string(j);
}

////////// Function for testing function pointers //////////
void functionpointer() {
	std::vector<double> numbers = { 1, 2, 3, 4, 5 };

	std::cout << "Function Pointer:" << std::endl;

	std::cout 	<< "Init:\t[ " 
		<< reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	map_funcpointer(numbers.begin(), numbers.end(), numbers.begin(), square);

	std::cout 	<< "Map:\t[ " 
		<< reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	filter_funcpointer(numbers.begin(), numbers.end(), numbers.begin(), is_odd);

	std::cout 	<< "Filter:\t[ " 
		<< reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

 	std::cout 	<< "Reduce:\t" 
 		<< reduce_funcpointer(numbers.begin(), numbers.end(), 0.0, sum) 
 		<< std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Exercise 5.4 Functors
////////////////////////////////////////////////////////////////////////////////

// for map
class Square {
	public:
		Square() {}
		double operator()(double i) {
			return i * i;
		}

		/*
		 * used for 5.6
		 */
		double invert (double i) {
			return std::sqrt(i);
		}
};

// for filter
class Odd {
	public:
		Odd() {}
		bool operator()(int i) {
			return i % 2 == 1 ? true : false;
		}
};

// for reduce
class Sum {
	public:
		Sum() {}
		int operator()(int i, int j) {
			return i + j;
		}
};

template<typename InIt, typename OutIt>
OutIt map_functor(InIt first, InIt last, OutIt out_first, Square s) {
	while(first != last) { *out_first++ = s(*first++); }
	return out_first;
}

template<typename ItType, typename OutIt>
ItType filter_functor(ItType first, ItType last, OutIt out_first, Odd pred) {
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
T reduce_functor(ItType first, ItType last, T init, Sum s) {
	while(first != last) {
        init = s(init, *first++);
    }
    return init;
}

void functors() {
	std::vector<double> numbers = { 1, 2, 3, 4, 5 };

	std::cout << "Functors:" << std::endl;

	std::cout << "Init:\t[ " << reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
		<< std::endl;

	map_functor(numbers.begin(), numbers.end(), numbers.begin(), Square());

	std::cout << "Map:\t[ " << reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
		<< std::endl;

	filter_functor(numbers.begin(), numbers.end(), numbers.begin(), Odd());

	std::cout << "Filter:\t[ " << reduce_funcpointer(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
		<< std::endl;

	std::cout << "Reduce:\t" << reduce_functor(numbers.begin(), numbers.end(), 0, Sum()) << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Exercise 5.5 Templates
////////////////////////////////////////////////////////////////////////////////

template <typename InIt, typename OutIt, typename FuncType>
OutIt map_template(InIt first, InIt last, OutIt out_first, FuncType func) {
	while(first != last) {
		*out_first++ = func(*first++);
	}
	return out_first;
}

template <typename ItType, typename OutIt, typename FuncType>
ItType filter_template(ItType first, ItType last, OutIt out_first, FuncType pred) {
	while(first != last) {
		if(pred(*first)) {
			*out_first++ = *first++;
		} else {
			++first;
		}
	}
	return out_first;
}

template <typename ItType, typename T, typename FuncType> 
T reduce_template(ItType first, ItType last, T init, FuncType func) {
	while(first != last) {
		init = func(init, *first++);
	}
	return init;
}
 

////////////////////////////////////////////////////////////////////////////////
// Exercise 5.6 Methodpointers
////////////////////////////////////////////////////////////////////////////////

template <typename InIt, typename OutIt, typename ObjType>
OutIt map_method(InIt first, InIt last, 
		OutIt out_first, ObjType *object, double (ObjType::* method)(double)) {
	while(first != last) {
		*out_first++ = (object->*method)(*first++);
	}
	return out_first;
}

class Sine {
	public:
		double operator()(double i) {
			return std::sin(i); }

		double invert(double i) {
			return std::asin(i);
		}
};

void methodpointers() {
	std::vector<double> numbers = { .1, .2, .3, .4, .5 };

	std::cout << "Method pointers:" << std::endl;

	std::cout 	<< std::left << std::setw(18) 
		<< "Init:" << "\t[ " 
		<< reduce_template(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	map_method(numbers.begin(), numbers.end(), numbers.begin(), new Square(), &Square::operator());

	std::cout 	<< std::left << std::setw(18)
		<< "Square::operator():" << "\t[ " 
		<< reduce_template(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	map_method(numbers.begin(), numbers.end(), numbers.begin(), new Square(), &Square::invert);

	std::cout 	<< std::left << std::setw(18)
		<< "Square::invert:" << "\t[ " 
		<< reduce_template(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	map_method(numbers.begin(), numbers.end(), numbers.begin(), new Sine(), &Sine::operator());

	std::cout 	<< std::left << std::setw(18)
		<< "Sine::operator():" << "\t[ " 
		<< reduce_template(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;

	map_method(numbers.begin(), numbers.end(), numbers.begin(), new Sine(), &Sine::invert);

	std::cout 	<< std::left << std::setw(18)
		<< "Sine::invert:" << "\t[ " 
		<< reduce_template(numbers.begin(), numbers.end(), std::string{}, to_string<double>) 
		<< " ]"
		<< std::endl;
}

int main() {
	functionpointer();
	std::cout << std::string(40, '-') << std::endl;
	functors();
	std::cout << std::string(40, '-') << std::endl;
	methodpointers();
}
