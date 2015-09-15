#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

class Vector3 {
public:
	Vector3();								// initialize vector with zero
	Vector3(double a, double b, double c);	// initialize vector with a, b, c
	Vector3(const Vector3& other);			// copy constructor: copy a vector
	~Vector3();								// destructor: destroy the vector
	
	Vector3 operator+(Vector3 rhs);			// add two vectors component-by-component
	Vector3 operator-(Vector3 rhs);			// subtract two vectors component-by-component
	double operator*(Vector3 rhs);			// determine the dot product of two vectors
	
	double getA();							// get the first component
	double getB();							// get the second component
	double getC();							// get the third component
private:
	double a, b, c;							// vector components
};

std::ostream& operator<<(std::ostream& out, Vector3 rhs);

#endif /* VECTOR3_HPP_ */
