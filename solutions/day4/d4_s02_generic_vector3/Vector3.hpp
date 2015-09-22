#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <memory>

template<typename T>
class Vector3 {
public:
	Vector3();

	Vector3(T a, T b, T c);

	Vector3(const Vector3& other);

	Vector3<T> operator+(const Vector3<T>& rhs) const;

	Vector3<T> operator-(const Vector3<T>& rhs) const;

	T operator*(const Vector3<T>& rhs) const;

	Vector3<T> operator*(const T& rhs) const;

	Vector3<T> operator/(const T& rhs) const;

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

// The following does not work! C++ does not support templates for typedefs
//template<class T>
//typedef std::shared_ptr<Vector3<T>> VectorPtr;

// C++11 introduces the following syntax:
template<typename T>
using Vector3Ptr = std::shared_ptr<Vector3<T>>;

// Alternatively, you may use template specializations for typedefs:
typedef std::shared_ptr<Vector3<double>> DoubleVectorPtr;

#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T> rhs);

#include "Vector3.tpp"

#endif /* VECTOR3_HPP_ */
