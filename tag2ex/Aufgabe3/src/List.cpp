/*
 * List.cpp
 *
 *  Created on: Aug 11, 2013
 *      Author: jgdo
 */

#include <cstdlib>
#include "List.h"

List::List() :
		first(NULL), last(NULL), currentSize(0) {
}

List::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0)
		deleteFirst();
}

void List::appendElement(int i) {
	ListItem *item = new ListItem(last, NULL, i);
	last = item;
	
	// if size WAS 0, set first item to newly created item
	if (currentSize++ == 0) 
		first = item;
}

void List::prependElement(int i) {
	ListItem *item = new ListItem(NULL, first, i);
	first = item;
	
	// if size WAS 0, set last item to newly created item
	if (currentSize++ == 0)
		last = item;
}

int List::getSize() const {
	return currentSize;
}

int& List::getNthElement(int n) {
	ListItem* p = first;
	// iterate over elements
	while (n-- > 0)
		p = p->getNext();
	
	return p->getContent();
}

int& List::getFirst() {
	return first->getContent();
}

int& List::getLast() {
	return last->getContent();
}

int List::deleteFirst() {
	if (first) {
		int content = first->getContent();
		
		ListItem *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		
		if (next == NULL) // do not forget to reset last element if list is empty
			last = NULL;
		
		currentSize--;
		return content;
	} else
		return 0;
}

int List::deleteLast() {
	if (last) {
		int content = last->getContent();
		
		ListItem *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		
		if (last == NULL) // do not forget to reset first element if list is empty
			first = NULL;
		
		currentSize--;
		return content;
	} else
		return 0;
}

ListIterator List::begin() {
	return ListIterator(this, first);
}
ListIterator List::end() {
	return ListIterator(this, NULL);
}
