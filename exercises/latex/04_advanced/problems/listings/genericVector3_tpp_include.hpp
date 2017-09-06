#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

/**
 * Don't forget documentation!
 */
template<typename T>
class Vector3 {
public:
    // Method declarations

    // You need to use a different template type if you want to declare the
    // overloaded output operator as friend.
    // Otherwise, you can introduce getters for the vector attributes.
    // Then there is no need to use a friend declaration.
    template<typename X>
    friend std::ostream& operator<<(std::ostream& out, const Vector3<X> rhs);

private:
    // Attributes
};

// function declarations only

#include "Vector3.tpp" // contains method and function definitions

#endif /* VECTOR3_HPP_ */