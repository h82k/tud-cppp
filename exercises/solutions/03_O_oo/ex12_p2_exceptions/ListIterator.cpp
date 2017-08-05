#include "ListIterator.hpp"
#include "ListItem.hpp"
#include "List.hpp"

#include <cstdlib>

ListIterator::ListIterator(const List* list, ListItem* item):
	list(list), item(item)
{}


ListIterator& ListIterator::operator++() {
	if (item == nullptr) {
		item = list->first;
	}
	else {
		item = item->getNext();
	}
	return *this;
}


ListIterator ListIterator::operator++(int) {
	ListIterator iter(list, item);
	if (item == nullptr) {
		item = list->first;
	}
	else {
		item = item->getNext();
	}
	return iter;
}


ListIterator& ListIterator::operator--() {
	if (item == NULL) {
		item = list->last;
	}
	else {
		item = item->getPrevious();
	}
	return *this;
}


ListIterator ListIterator::operator--(int) {
	ListIterator iter(list, item);
	if (item == NULL) {
		item = list->last;
	}
	else {
		item = item->getPrevious();
	}
	return iter;
}


int& ListIterator::operator*() {
	return item->getContent();
}


bool ListIterator::operator!=(const ListIterator& other) const {
	return (item != other.item) || (list != other.list);
}
