template<typename T>
Vector3<T>::Vector3():
	a(0), b(0), c(0)
{}

template<typename T>
Vector3<T>::Vector3(T a, T b, T c):
	a(a), b(b), c(c)
{}

template<typename T>
Vector3<T>::Vector3(const Vector3& other):
	a(other.a), b(other.b), c(other.c)
{}

template<typename T>
T Vector3<T>::operator*(const Vector3& rhs) const {
	return a * rhs.a + b * rhs.b + c * rhs.c;
}

// The parameter T in Vector3<T> must only be used inside the class scope
// and as a return type in the pre-C++11 function header:
//		Vector3<T> Vector3<T>::functionName(...) {...}
// If using the new C++11 trailing return type syntax one may ommit the <T> and write instead:
//		auto Vector3<T>::functionName(...) -> Vector3 {...}
// In general, the parameter T may be ommitted inside the parameter list and the function body.

template<typename T>
//Vector3<T> Vector3<T>::operator+(const Vector3& rhs) const {
auto Vector3<T>::operator+(const Vector3& rhs) const -> Vector3 {
	return Vector3(a + rhs.a, b + rhs.b, c + rhs.c);
}

template<typename T>
//Vector3<T> Vector3<T>::operator-(const Vector3& rhs) const {
auto Vector3<T>::operator-(const Vector3& rhs) const -> Vector3 {
	return Vector3(a - rhs.a, b - rhs.b, c - rhs.c);
}

template<typename T>
//Vector3<T> Vector3<T>::operator*(const T& rhs) const {
auto Vector3<T>::operator*(const T& rhs) const -> Vector3 {
	return Vector3(a * rhs, b * rhs, c * rhs);
}

template<typename T>
//Vector3<T> Vector3<T>::operator/(const T& rhs) const {
auto Vector3<T>::operator/(const T& rhs) const -> Vector3 {
	return Vector3(a / rhs, b / rhs, c / rhs);
}

// In the following function the parameter T must be used as a parameter to
// Vector3 because the function resides outside of the Vector3<T> class scope.
template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T> rhs) {
	out << "(" << rhs.getA() << ", " << rhs.getB() << ", " << rhs.getC() << ")";
	return out;
}
