#include "List.hpp"
#include "ListItem.hpp"
#include <cstddef>

List::List():
	first(NULL), last(NULL), currentSize(0)
{}

List::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0) {
		deleteFirst();
	}
}

List::List(const List& other):
	first(NULL), last(NULL), currentSize(0)
{
	// Copy list item-wise to avoid having two lists pointing at the same list items
	for (ListItem *item = other.first; item != NULL; item = item->getNext()) {
		appendElement(item->getContent());
	}
}

void List::appendElement(int i) {
	ListItem *item = new ListItem(last, NULL, i);
	last = item;
	if (first == NULL) {
		first = item;
	}
	++currentSize;
}

void List::prependElement(int i) {
	ListItem *item = new ListItem(NULL, first, i);
	first = item;
	if (last == NULL) {
		last = item;
	}
	++currentSize;
}

void List::insertElementAt(int i, int pos) {
	if (pos <= 0) {
		prependElement(i);
	}
	if (pos >= getSize()) {
		appendElement(i);
	}
	else {
		ListItem* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		new ListItem(p->getPrevious(), p, i);
		++currentSize;
	}
}

int List::getSize() const {
	return currentSize;
}

int& List::getNthElement(int n) {
	int index = n;
	ListItem* p = first;
	// iterate over elements
	while (index-- > 0) {
		p = p->getNext();
	}
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
		int content = first->getContent(); // save content
		ListItem *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		if (next == NULL) {// do not forget to reset last element if list is empty
			last = NULL;
		}
		--currentSize;
		return content;
	}
	return 0;
}

int List::deleteLast() {
	if (last) {
		int content = last->getContent();
		ListItem *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		if (last == NULL) {// do not forget to reset first element if list is empty
			first = NULL;
		}
		--currentSize;
		return content;
	}
	return 0;
}

int List::deleteAt(int pos) {
	if (pos <= 0) {
		return deleteFirst();
	}
	else if (pos >= currentSize - 1) {
		return deleteLast();
	}
	else {
		int index = pos;
		ListItem* p = first;
		// iterate over elements
		while (index-- > 0) {
			p = p->getNext();
		}
		int content = p->getContent();
		delete p;
		--currentSize;
		return content;
	}
}

ListIterator List::begin() {
	return ListIterator(this, first);
}
ListIterator List::end() {
	return ListIterator(this, NULL);
}
