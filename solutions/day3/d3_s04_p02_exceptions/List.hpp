#ifndef LIST_HPP_
#define LIST_HPP_

#include "ListIterator.hpp"
#include <iostream>
#include <stdexcept>

class ListItem;

class List {
public:
	/** Create an empty list */
	List();

	/** Delete the list and all elements */
	~List();

	/** Create List as copy of other list */
	List(const List& other);

	/** append an element to end of the list */
	void appendElement(const int& i);

	/** prepend an element to beginning of the list */
	void prependElement(const int& i);

	/** insert element at position pos. throws out_of_range if pos is out of range */
	void insertElementAt(const int& i, int pos);

	/** number of elements in list */
	int getSize() const;

	/* return n-th element. throws out_of_range if pos is out of range. slow! */
	int& getNthElement(int n);

	/** return first element */
	int& getFirst();

	/** return last element */
	int& getLast();

	/** delete first element */
	void deleteFirst();

	/** delete last element */
	void deleteLast();

	/** delete element at given position. throws out_of_range if pos is out of range. */
	void deleteAt(int pos);

	/** iterator to first element */
	ListIterator begin() const;

	/** iterator to element after the last one*/
	ListIterator end() const;

private:
	/** first and last item pointers. NULL if list is empty */
	ListItem *first, *last;
	/** current size of the list */
	int currentSize;
	/** declare ListIterator as friend to allow access on list items */
	friend class ListIterator;
};

std::ostream &operator<<(std::ostream &stream, const List &list);

#endif /* LIST_HPP_ */
