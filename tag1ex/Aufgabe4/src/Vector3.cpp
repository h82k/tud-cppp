/*
 * Vektor3.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: jgdo
 */

#include "Vector3.h"

Vector3::Vector3() :
		a(0), b(0), c(0) {
}

Vector3::Vector3(double a, double b, double c) :
		a(a), b(b), c(c) {
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

ostream& operator<<(ostream& out, Vector3 rhs)  {
	out << "(" << rhs.getA() << ", " << rhs.getB() << ", " << rhs.getC() << ")";
	return out;
}
