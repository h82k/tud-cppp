#ifndef ARRAY_HPP_
#define ARRAY_HPP_

#include <iostream>
#include <memory>
#include <cstddef>

/**
 * Custom implementation of an array.
 *
 * This class encapsulates a raw array together with its size.
 *
 */
template<typename T>
class Array {
	typedef std::shared_ptr<T> TPtr;
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

template<typename T>
std::ostream &operator<<(std::ostream &stream, const Array<T> &array);

#include "Array.tpp"

#endif /* ARRAY_HPP_ */
