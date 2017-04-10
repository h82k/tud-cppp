#include "List.hpp"
#include "ListItem.hpp"

List::List() :
		first(nullptr), last(nullptr), currentSize(0) {
}

List::~List() {
	// just delete first element while list is not empty
	while (currentSize > 0) {
		deleteFirst();
	}
}

List::List(const List& other) :
		first(nullptr), last(nullptr), currentSize(0) {
	for (ListItem *item = other.first; item != nullptr; item = item->getNext()) {
		appendElement(item->getContent());
	}
}

void List::appendElement(const int &i) {
	ListItem *item = new ListItem(last, nullptr, i);
	last = item;
	// if size WAS 0, set first item to newly created item
	if (currentSize++ == 0) {
		first = item;
	}
}

void List::prependElement(const int &i) {
	ListItem *item = new ListItem(nullptr, first, i);
	first = item;
	// if size WAS 0, set last item to newly created item
	if (currentSize++ == 0) {
		last = item;
	}
}

void List::insertElementAt(const int &i, int pos) {
	if (pos < 0 || pos > getSize()) {
		throw std::out_of_range("List::insertElementAt() out of range");
	} else if (pos == 0) {
		prependElement(i);
	}
	if (pos == getSize()) {
		appendElement(i);
	} else {
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

int &List::getNthElement(int n) {
	if (n < 0 || n >= getSize()) {
		throw std::out_of_range("List::getNthElement() out of range");
	}
	ListItem* p = first;
	// iterate over elements
	while (n-- > 0) {
		p = p->getNext();
	}
	return p->getContent();
}

int &List::getFirst() {
	return first->getContent();
}

int &List::getLast() {
	return last->getContent();
}

void List::deleteFirst() {
	if (first) {
		ListItem *next = first->getNext();
		delete first; // delete first element
		first = next; // and the current first element to next of first element before
		// do not forget to reset last element if list is empty
		if (next == nullptr) {
			last = nullptr;
		}
		--currentSize;
	}
}

void List::deleteLast() {
	if (last) {
		ListItem *prev = last->getPrevious();
		delete last; // delete last element
		last = prev; // and the current last element to previous of last element before
		// do not forget to reset first element if list is empty
		if (last == nullptr) {
			first = nullptr;
		}
		--currentSize;
	}
}

/** delete element at given position. delete first/last if pos outside of range */

void List::deleteAt(int pos) {
	if (pos < 0 || pos >= getSize()) {
		throw std::out_of_range("List::deleteAt() out of range");
	} else if (pos == 0) {
		return deleteFirst();
	} else if (pos == getSize() - 1) {
		return deleteLast();
	} else {
		ListItem* p = first;
		// iterate over elements
		while (pos-- > 0) {
			p = p->getNext();
		}
		delete p;
		--currentSize;
	}
}

ListIterator List::begin() const {
	return ListIterator(this, first);
}

ListIterator List::end() const{
	return ListIterator(this, nullptr);
}

std::ostream& operator<<(std::ostream& out, const List& list) {
	out << "[";
	ListIterator iter = list.begin();
	if (iter != list.end()) {
		out << *iter++;
		while (iter != list.end()) {
			out << ", " << *iter++;
		}
	}
	out << "]";
	return out;
}
