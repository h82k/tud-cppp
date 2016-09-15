#include <iostream>
#include <vector>
#include <string>
#include <cmath> // for std::sin, std::asin
#include <iomanip> // for advanced output formatting, e.g., std::setw, std::left

// for map
double square(double i)
{
    return i * i;
}

// for filter
bool is_odd(int i)
{
    return i % 2 == 1 ? true : false;
}

// for reduce
double sum(double i, double j)
{
    return i + j;
}

template <class T> std::string to_string(std::string& str, const T& j)
{
    return str.empty() ? std::to_string(j) : str + " - " + std::to_string(j);
}

// for map
class Square
{
public:
    Square()
    {
    }
    double operator()(double i)
    {
	return i * i;
    }
	
	double invert (double i)
	{
		return std::sqrt(i);
	}
};

class Sine
{
public:
    double operator()(double i)
    {
	return std::sin(i);
    }

	double invert(double i)
	{
		return std::asin(i);
	}
};

// for filter
class Odd
{
public:
    Odd()
    {
    }
    bool operator()(int i)
    {
	return i % 2 == 1 ? true : false;
    }
};

// for reduce
class Sum
{
public:
    Sum()
    {
    }
    int operator()(int i, int j)
    {
	return i + j;
    }
};

template <typename InIt, typename OutIt, typename FuncType>
OutIt map(InIt first, InIt last, OutIt out_first, FuncType func)
{
    while(first != last) {
	*out_first++ = func(*first++);
    }
    return out_first;
}

template <typename InIt, typename OutIt, typename FuncType>
OutIt map(InIt first, InIt last, OutIt out_first, FuncType *object, double (FuncType::* method)(double))
{
    while(first != last) {
	*out_first++ = (object->*method)(*first++);
    }
    return out_first;
}

template <typename ItType, typename OutIt, typename FuncType>
ItType filter(ItType first, ItType last, OutIt out_first, FuncType pred)
{
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
T reduce(ItType first, ItType last, T init, FuncType func)
{
    while(first != last) {
	init = func(init, *first++);
    }
    return init;
}

void functionpointer()
{
    std::cout << "Function Pointer:" << std::endl;
    std::vector<double> numbers = { 1, 2, 3, 4, 5 };

    std::cout << "Init:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    map(numbers.begin(), numbers.end(), numbers.begin(), square);

    std::cout << "Map:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    filter(numbers.begin(), numbers.end(), numbers.begin(), is_odd);

    std::cout << "Filter:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    std::cout << "Reduce:\t" << reduce(numbers.begin(), numbers.end(), 0, sum) << std::endl;
}

void functors()
{
    std::cout << "Functors:" << std::endl;
    std::vector<double> numbers = { 1, 2, 3, 4, 5 };

    std::cout << "Init:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    map(numbers.begin(), numbers.end(), numbers.begin(), Square());

    std::cout << "Map:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    filter(numbers.begin(), numbers.end(), numbers.begin(), Odd());

    std::cout << "Filter:\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    std::cout << "Reduce:\t" << reduce(numbers.begin(), numbers.end(), 0, Sum()) << std::endl;
}

void methodpointers()
{
    std::cout << "Method pointersl:" << std::endl;
    std::vector<double> numbers = { .1, .2, .3, .4, .5 };

    std::cout << std::left << std::setw(18) << "Init:" << "\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;

    map(numbers.begin(), numbers.end(), numbers.begin(), new Square(), &Square::operator());

    std::cout << std::left << std::setw(18)<< "Square::operator():" << "\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;
			  
    map(numbers.begin(), numbers.end(), numbers.begin(), new Square(), &Square::invert);

    std::cout << std::left << std::setw(18)<< "Square::invert:" << "\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;
			  
    map(numbers.begin(), numbers.end(), numbers.begin(), new Sine(), &Sine::operator());

    std::cout << std::left << std::setw(18)<< "Sine::operator():" << "\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;
			  
    map(numbers.begin(), numbers.end(), numbers.begin(), new Sine(), &Sine::invert);

    std::cout << std::left << std::setw(18)<< "Sine::invert:" << "\t[ " << reduce(numbers.begin(), numbers.end(), std::string{}, to_string<double>) << " ]"
              << std::endl;
}

int main()
{
    functionpointer();
    std::cout << std::string(40, '-') << std::endl;
    functors();
    std::cout << std::string(40, '-') << std::endl;
	methodpointers();
}
