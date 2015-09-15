#ifndef LIST_HPP_
#define LIST_HPP_

#include "ListIterator.hpp"
#include <iostream>
#include <stdexcept>

class ListItem;

class List {
public:
	List();						// create an empty list
	~List();					// delete the list and all of its elements
	List(const List& other);	// create a copy of another list
	void appendElement(const int& i);	// append an element to the end of the list
	void prependElement(const int& i);	// prepend an element to the beginning of the list
	void insertElementAt(const int& i, int pos);	// insert an element i at position pos
	int getSize() const;		// get the number of elements in list
	int& getNthElement(int n);	// get content of the n-th element.
	int& getFirst();			// get content of the first element
	int& getLast();				// get content of the last element
	void deleteFirst();			// delete first element
	void deleteLast();			// delete last element
	void deleteAt(int pos);		// delete element at position pos
	ListIterator begin() const;	// return an iterator pointing to the first element
	ListIterator end() const;	// return an iterator pointing to the element after the last one
private:
	ListItem *first, *last;		// first and last item pointers (NULL if list is empty)
	int currentSize;			// current size of the list
	friend class ListIterator;
};

std::ostream &operator<<(std::ostream &stream, const List &list);

#endif /* LIST_HPP_ */
