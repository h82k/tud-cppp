#include "Vector3.hpp"


Vector3::Vector3():
	a(0), b(0), c(0)
{
	std::cout << "creating Vector3()" << std::endl;
}

Vector3::Vector3(double a, double b, double c):
	a(a), b(b), c(c)
{
	std::cout << "creating Vector3(" << a << ", " << b << ", " << c << ")" << std::endl;
}

Vector3::Vector3(const Vector3& other):
	a(other.a), b(other.b), c(other.c)
{
	std::cout << "copying Vector3(" << a << ", " << b << ", " << c << ")" << std::endl;
}

Vector3::~Vector3() {
	std::cout << "deleting Vector3(" << a << ", " << b << ", " << c << ")" << std::endl;
}

Vector3 Vector3::operator+(Vector3 rhs) {
	return Vector3(a + rhs.a, b + rhs.b, c + rhs.c);
}

Vector3 Vector3::operator-(Vector3 rhs) {
	return Vector3(a - rhs.a, b - rhs.b, c - rhs.c);
}

double Vector3::operator*(Vector3 rhs) {
	return a * rhs.a + b * rhs.b + c * rhs.c;
}

ostream& operator<<(ostream& out, Vector3 rhs) {
	out << "(" << rhs.getA() << ", " << rhs.getB() << ", " << rhs.getC() << ")";
	return out;
}
