#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <memory>

template<typename T>
class Vector3 {
public:
	Vector3() :
			a(0), b(0), c(0) {
	}
	
	Vector3(T a, T b, T c) :
			a(a), b(b), c(c) {
	}
	
	Vector3(const Vector3& other) :
			a(other.a), b(other.b), c(other.c) {
	}
	
	Vector3<T> operator+(const Vector3<T>& rhs) const {
		return Vector3(a + rhs.a, b + rhs.b, c + rhs.c);
	}
	
	Vector3<T> operator-(const Vector3<T>& rhs) const {
		return Vector3(a - rhs.a, b - rhs.b, c - rhs.c);
	}
	
	T operator*(const Vector3<T>& rhs) const {
		return a * rhs.a + b * rhs.b + c * rhs.c;
	}
	
	Vector3<T> operator*(const T& rhs) const {
		return Vector3(a * rhs, b * rhs, c * rhs);
	}
	
	Vector3<T> operator/(const T& rhs) const {
		return Vector3(a / rhs, b / rhs, c / rhs);
	}
	
	T getA() const {
		return a;
	}
	
	T getB() const {
		return b;
	}
	
	T getC() const {
		return c;
	}
private:
	T a, b, c;
};

// C++ does not support templates for typedefs
//template<typename T>
//typedef std::shared_ptr<Vector3<T>> VectorPtr;

// C++11 introduces the following syntax:
template<typename T>
using Vector3Ptr = std::shared_ptr<Vector3<T>>;

// Alternative:
typedef std::shared_ptr<Vector3<double>> DoubleVectorPtr;

#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T> rhs) {
	out << "(" << rhs.getA() << ", " << rhs.getB() << ", " << rhs.getC() << ")";
	return out;
}

#endif /* VECTOR3_HPP_ */
