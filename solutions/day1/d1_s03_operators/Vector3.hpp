#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

/**
 * @name Vector3
 * @brief self-made vector class with 3 elements.
 * @author cppp
 */
class Vector3 {
    /**
     * @name operator<<(std:ostream&, Vector3);
     * @brief operator overloading to print out vector using <<
     * @author cppp
     * @param stdout implicitly given by *std::cout <<* ..
     * @param Vector3 implicitly given by .. *<< vector* ..
     */
	friend std::ostream& operator<<(std::ostream&, Vector3);
public:

    /**
     * @name Vector3();
     * @brief constructs a (0,0,0)^t vector
     * @author cppp
     */
	Vector3();								// initialize vector with zero
    /**
     * @name Vector3(double a, double b, double c);
     * @brief constructs a (a, b, c)^t vector
     * @author cppp
     * @param a first element of vector
     * @param b first element of vector
     * @param c first element of vector
     */
	Vector3(double a, double b, double c);	// initialize vector with a, b, c
    /**
     * @name Vector3(const Vector3& other);
     * @brief copy constructor of Vector3
     * @author cppp
     * @param other the copied vector
     */
	Vector3(const Vector3& other);			// copy constructor: copy a vector
    /**
     * @name ~Vector3();
     * @brief destructor
     * @author cppp
     */
	~Vector3();								// destructor: destroy the vector
	
    /**
     * @name operator+(Vector3 rhs);
     * @brief operator overloading to add a vector to another
     * @author cppp
     * @param rhs the vector which will be added to the given vector object
     */
	Vector3 operator+(Vector3 rhs);			// add two vectors component-by-component
    /**
     * @name operator-(Vector3 rhs);
     * @brief operator overloading to subtract a vector to another
     * @author cppp
     * @param rhs the vector which will be subtracted 
     */
	Vector3 operator-(Vector3 rhs);			// subtract two vectors component-by-component
    /**
     * @name operator*(Vector3 rhs);
     * @brief operator overloading to build a dot product of two vertices 
     * @author cppp
     * @param rhs the vector with which the dot product will be computed
     * @return the dot product
     */
	double operator*(Vector3 rhs);			// determine the dot product of two vectors
	
    /**
     * @name getA();
     * @brief returns a
     * @author cppp
     * @return this->a 
     */
	double getA();							// get the first component
    /**
     * @name getB();
     * @brief returns b
     * @author cppp
     * @return this->b
     */
	double getB();							// get the second component
    /**
     * @name getC();
     * @brief returns c
     * @author cppp
     * @return this->c
     */
	double getC();							// get the third component
private:
	double a, b, c;							// vector components
};


#endif /* VECTOR3_HPP_ */
