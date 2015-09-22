template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T> rhs) {
	out << "(" << rhs.getA() << ", " << rhs.getB() << ", " << rhs.getC() << ")";
	return out;
}
template<typename T> Vector3<T>::Vector3() :
		a(0), b(0), c(0) {
}

template<typename T> Vector3<T>::Vector3(T a, T b, T c) :
		a(a), b(b), c(c) {
}

template<typename T> Vector3<T>::Vector3(const Vector3& other) :
		a(other.a), b(other.b), c(other.c) {
}

template<typename T> Vector3<T> Vector3<T>::operator+(
		const Vector3<T>& rhs) const {
	return Vector3(a + rhs.a, b + rhs.b, c + rhs.c);
}

template<typename T> Vector3<T> Vector3<T>::operator-(
		const Vector3<T>& rhs) const {
	return Vector3(a - rhs.a, b - rhs.b, c - rhs.c);
}
template<typename T>
T Vector3<T>::operator*(const Vector3<T>& rhs) const {
	return a * rhs.a + b * rhs.b + c * rhs.c;
}
template<typename T>
Vector3<T> Vector3<T>::operator*(const T& rhs) const {
	return Vector3(a * rhs, b * rhs, c * rhs);
}
template<typename T>
Vector3<T> Vector3<T>::operator/(const T& rhs) const {
	return Vector3(a / rhs, b / rhs, c / rhs);
}
