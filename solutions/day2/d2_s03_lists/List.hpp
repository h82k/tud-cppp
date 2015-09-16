#ifndef LIST_HPP_
#define LIST_HPP_

#include "ListIterator.hpp"
class ListItem;

class List {
public:
	List();						// create an empty list
	~List();					// delete the list and all of its elements
	List(const List& other);	// create a copy of another list
	void appendElement(int i);	// append an element to the end of the list
	void prependElement(int i);	// prepend an element to the beginning of the list
	void insertElementAt(int i, int pos);	// insert an element i at position pos
	int getSize() const;		// get the number of elements in list
	int& getNthElement(int n);	// get content of the n-th element.
	int& getFirst();			// get content of the first element
	int& getLast();				// get content of the last element
	int deleteFirst();			// delete first element and return it (return 0 if empty)
	int deleteLast();			// delete last element and return it (return 0 if empty)
	int deleteAt(int pos);		// delete element at position pos
	ListIterator begin();		// return an iterator pointing to the first element
	ListIterator end();			// return an iterator pointing to the element after the last one
private:
	ListItem *first, *last;		// first and last item pointers (NULL if list is empty)
	int currentSize;			// current size of the list
	friend class ListIterator;
};

#include <iostream>

/** Print the given list to the stream. N.B. list should actually be const but then we would need const ListIterators */
std::ostream &operator<<(std::ostream &stream, List &list);

#endif /* LIST_HPP_ */
