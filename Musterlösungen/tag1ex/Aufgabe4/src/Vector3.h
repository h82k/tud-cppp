/*
 * Vector3.h
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <iostream>
using namespace std;

class Vector3 {
public:
	Vector3();
	Vector3(double a, double b, double c);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(Vector3 rhs);
	Vector3 operator-(Vector3 rhs);
	double operator*(Vector3 rhs);

	inline double getA() {
		return a;
	}
	
	inline double getB() {
		return b;
	}
	
	inline double getC() {
		return c;
	}
	
private:
	double a, b, c;
};

ostream& operator<<(ostream& out, Vector3 rhs);

#endif /* VECTOR3_H_ */
