#include <iostream>

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
