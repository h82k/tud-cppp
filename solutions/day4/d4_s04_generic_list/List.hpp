#ifndef LIST_HPP_
#define LIST_HPP_

#include <cstdlib>
#include "ListItem.hpp"
#include "ListIterator.hpp"
#include <iostream>

template<class T>
class List {
public:
	/** Create an empty list */
	List();

	/** Delete the list and all elements */
	~List();

	/** Create List as copy of other list */
	List(const List<T>& other);

	/** append an element to end of the list */
	void appendElement(const T& i);

	/** prepend an element to beginning of the list */
	void prependElement(const T& i);

	/** insert element at position pos. append/prepend element if pos outside of range*/
	void insertElementAt(const T& i, int pos);

	/** number of elements in list */
	int getSize() const;

	/* return n-th element. No range checks. slow! */
	T& getNthElement(int n);

	/** return first element */
	T& getFirst();

	/** return last element */
	T& getLast();

	/** delete first element */
	void deleteFirst();

	/** delete last element */
	void deleteLast();

	/** delete element at given position. delete first/last if pos outside of range */
	void deleteAt(int pos);

	/** iterator to first element */
	ListIterator<T> begin();

	/** iterator to element after the last one*/
	ListIterator<T> end();
private:
	/** first and last item pointers. NULL if list is empty */
	ListItem<T> *first, *last;
	/** current size of the list */
	int currentSize;
	/** declare ListIterator as friend to allow access on list items */
	friend class ListIterator<T> ;
};

#include "List.tpp"

#endif /* LIST_HPP_ */
