#ifndef LIST_HPP_
#define LIST_HPP_

#include <cstdlib>
#include "ListItem.hpp"
#include "ListIterator.hpp"
#include <iostream>

template<typename T>
class List {
public:
	List();						// create an empty list
	~List();					// delete the list and all of its elements
	List(const List& other);	// create a copy of another list
	void appendElement(const T& i);				// append an element to the end of the list
	void prependElement(const T& i);			// prepend an element to the beginning of the list
	void insertElementAt(const T& i, int pos);	// insert an element i at position pos
	int getSize() const;		// get the number of elements in list
	T& getNthElement(int n);	// get content of the n-th element.
	T& getFirst();				// get content of the first element
	T& getLast();				// get content of the last element
	void deleteFirst();			// delete first element
	void deleteLast();			// delete last element
	void deleteAt(int pos);		// delete element at position pos
	ListIterator<T> begin();	// return an iterator pointing to the first element
	ListIterator<T> end();		// return an iterator pointing to the element after the last one
private:
	ListItem<T> *first, *last;	// first and last item pointers (NULL if list is empty)
	int currentSize;			// current size of the list
	friend class ListIterator<T>;
};

#include "List.tpp"

#endif /* LIST_HPP_ */
