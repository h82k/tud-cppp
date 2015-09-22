#include <stdexcept>
#include <cstdlib>
#include <sstream>

template<typename T>
struct array_deleter {
	void operator ()(T const * p) {
		delete[] p;
	}
};

template<typename T>
Array<T>::Array(size_t size):
	size(size), offset(0)
{
	data = TPtr(new T[size], array_deleter<T>());
}

template<typename T>
Array<T>::Array(const Array<T> &other, size_t offset):
	size(other.size), data(other.data), offset(offset)
{}

template<typename T>
Array<T>::~Array() {}

template<typename T>
size_t Array<T>::getSize() const {
	return size - offset;
}

template<typename T>
T &Array<T>::operator [](size_t index) {
	if (index >= getSize()) {
		std::stringstream message;
		message << "Index out of bounds. Index: " << index << ", size: " << getSize() << ".";
		throw std::out_of_range(message.str());
	}
	return (data.get())[index + offset];
}

template<typename T>
const T &Array<T>::operator [](size_t index) const {
	if (index >= getSize()) {
		std::stringstream message;
		message << "Index out of bounds. Index: " << index << ", size: " << getSize() << ".";
		throw std::out_of_range(message.str());
	}
	return (data.get())[index + offset];
}

template<typename T>
Array<T> Array<T>::operator+(size_t delta) {
	if (delta >= getSize()) {
		std::stringstream message;
		message << "Offset larger than array size. Offset: " << delta << ", size: " << getSize() << ".";
		throw std::out_of_range(message.str());
	}
	Array<T> offsetArray(*this, offset + delta);
	return offsetArray;
}
