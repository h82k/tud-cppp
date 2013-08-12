/*
 * List.h
 *
 *  Created on: Aug 11, 2013
 *      Author: jgdo
 */

#ifndef LIST_H_
#define LIST_H_

#include "ListItem.h"
#include "ListIterator.h"

class List {
public:
	/** Create an empty list */
	List();

	/** Delete the list and all elements */
	~List();

	/** append an element to end of the list */
	void appendElement(int i);

	/** prepend an element to beginning of the list */
	void prependElement(int i);

	/** number of elements in list */
	int getSize() const;

	/* return n-th element. No range checks. slow! */
	int& getNthElement(int n);

	/** return first element */
	int& getFirst();

	/** return last element */
	int& getLast();

	/** delete first element and return it. If list was empty, return 0. */
	int deleteFirst();

	/** delete last element and return it. If list was empty, return 0. */
	int deleteLast();

	/** iterator to first element */
	ListIterator begin();

	/** iterator to element after the last one*/
	ListIterator end();

private:
	/** first and last item pointers. NULL if list is empty */
	ListItem *first, *last;

	/** current size of the list */
	int currentSize;

	/** declare ListIterator as friend to allow access on list items */
	friend class ListIterator;
};

#endif /* LIST_H_ */
