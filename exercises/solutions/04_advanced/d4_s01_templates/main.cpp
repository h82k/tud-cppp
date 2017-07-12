#include <iostream>

/**
 * Reasons for returning by const reference:
 *  * If T is a 'complex type' (e.g., a fat class), that returning by value would incur extra cost
 *    in terms of memory and time for copying either t1 or t2. 
 *    Additionally, some classes may not even support copying (see lecture slides).
 *  * It would also be possible to return by pointer-to-const here, but using a reference 
 *    (i) is more convenient for the caller, (ii) asserts that the return value is non-null
 *  * The return value cannot be non-const because the parameters are both const.
 */
template<typename T>
const T& maximum(const T& t1, const T& t2) {
	return t1 > t2 ? t1 : t2;
}

class C {
public:
	C(int number):
		number(number)
	{}
	bool operator>(const C& other) const {
		return number > other.number;
	}
	int getNumber() const {
		return number;
	}
private:
	int number;
};

std::ostream& operator<<(std::ostream& out, const C& c) {
	return out << c.getNumber();
}

int main() {
	// Aufgabe a)
	C c1(23), c2(42);
	std::cout << maximum(c1, c2) << std::endl;
	
	int i = 1;
	short s = 2;
	std::cout << maximum<int>(i, s) << std::endl;
}
