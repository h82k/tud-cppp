#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <iostream>
#include <boost/smart_ptr.hpp>

/**
 * Custom implementation of an array.
 *
 * This class encapsulates a raw array together with its size.
 *
 */
template<class T>
class Array {
	typedef boost::shared_ptr<T> TPtr;
public:
	/**
	 * Creates an array that can hold 'size'
	 * elements of its contained type.
	 */
	Array(size_t size);
	~Array();

	/**
	 * Returns the element of the array at the
	 * given index.
	 */
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	/**
	 * Returns an array that starts 'offset'
	 * items behind the current array.
	 */
	Array<T> operator+(size_t offset);

	/**
	 * Returns the size of this array.
	 */
	size_t getSize() const;

private:
	/**
	 * Internal constructor that produces a 'view' of the array
	 * that is shifted by 'offset'.
	 *
	 * Example:
	 * Given an array of size 10 and an offset of 2, the created array
	 * will have a size of 8 and its first element will be the third
	 * element of 'other'.
	 */
	Array(const Array<T> &other, size_t offset);

	/**
	 * The size of the underlying array.
	 * The true size is size - offset.
	 */
	size_t size;

	/**
	 * The underlying array, may be shared by multiple arrays that
	 * represent shifted views of the same underlying data.
	 */
	TPtr data;

	/**
	 * The offset in the underlying array.
	 */
	size_t offset;
};

template<class T>
std::ostream &operator<<(std::ostream &stream, const Array<T> &array);

#include <stdexcept>
#include <cstdlib>
#include <sstream>

template<typename T>
struct array_deleter {
	void operator ()(T const * p) {
		delete[] p;
	}
};

template<class T>
Array<T>::Array(size_t size) :
		size(size), offset(0) {
	data = TPtr(new T[size], array_deleter<T>());
}

template<class T>
Array<T>::Array(const Array<T> &other, size_t offset) :
		size(other.size), data(other.data), offset(offset) {
}

template<class T>
Array<T>::~Array() {
}

template<class T>
size_t Array<T>::getSize() const {
	return size - offset;
}

template<class T>
T &Array<T>::operator [](size_t index) {
	if (index >= getSize()) {
		std::stringstream message;
		message << "Index out of bounds. Index: " << index << ", size: "
				<< getSize() << ".";
		throw std::out_of_range(message.str());
	}
	return (data.get())[index + offset];
}

template<class T>
const T &Array<T>::operator [](size_t index) const {
	if (index >= getSize()) {
		std::stringstream message;
		message << "Index out of bounds. Index: " << index << ", size: "
				<< getSize() << ".";
		throw std::out_of_range(message.str());
	}
	return (data.get())[index + offset];
}

template<class T>
Array<T> Array<T>::operator+(size_t delta) {
	if (delta >= getSize()) {
		std::stringstream message;
		message << "Offset larger than array size. Offset: " << delta
				<< ", size: " << getSize() << ".";
		throw std::out_of_range(message.str());
	}
	Array<T> offsetArray(*this, offset + delta);
	return offsetArray;
}

#endif /* ARRAY_HPP_ */
