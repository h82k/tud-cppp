#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <memory>

/**
 * @name Vector
 * @author cppp
 * @brief Vector class using a template type T
 */
template<typename T>
class Vector3 {
public:
    /**
     * @name Vector3();
     * @brief constructs a (0,0,0)^t vector
     * @author cppp
     */
	Vector3();
    /**
     * @name Vector3(T a, T b, T c);
     * @brief constructs a (a, b, c)^t vector
     * @author cppp
     * @param a of type T
     * @param b of type T
     * @param c of type T
     */
	Vector3(T a, T b, T c);
    /**
     * @name Vector3(const Vector3& other);
     * @brief copy constructor of Vector3
     * @author cppp
     * @param other the copied vector
     */
	Vector3(const Vector3& other);
	
    /**
     * @name operator*(Vector3 rhs);
     * @brief operator overloading to build a dot product of two vertices 
     * @author cppp
     * @param rhs the vector with which the dot product will be computed
     * @return the dot product with type T
     */
	T operator*(const Vector3& rhs) const;
	
    
    /**
     * @name operator+(Vector3 rhs);
     * @brief operator overloading to add a vector to another
     * @author cppp
     * @param rhs the vector which will be added
     * @return resulted vector
     */
	Vector3 operator+(const Vector3& rhs) const;
    /**
     * @name operator-(Vector3 rhs);
     * @brief operator overloading to subtract a vector to another
     * @author cppp
     * @param rhs the vector which will be subtracted 
     * @return resulted vector
     */
	Vector3 operator-(const Vector3& rhs) const;
    /**
     * @name operator*(Vector3 rhs);
     * @brief operator overloading to multiply two vectices
     * @author cppp
     * @param rhs the other vector
     * @return resulted vector
     */
	Vector3 operator*(const T& rhs) const;
    /**
     * @name operator/(Vector3 rhs);
     * @brief operator overloading to divide two vectices
     * @author cppp
     * @param rhs the vector with with the base vector will be devided
     * @return resulted vector
     */
	Vector3 operator/(const T& rhs) const;
	
    /**
     * @name getA();
     * @brief returns a
     * @author cppp
     * @return this->a 
     */
	T getA() const {
		return a;
	}
	
    /**
     * @name getB();
     * @brief returns b
     * @author cppp
     * @return this->b 
     */
	T getB() const {
		return b;
	}
	
    /**
     * @name getC();
     * @brief returns c
     * @author cppp
     * @return this->c
     */
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
