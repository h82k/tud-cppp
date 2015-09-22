#include <cstddef>

template<typename T>
ListIterator<T>::ListIterator(List<T>* list, ListItem<T>* item):
	list(list), item(item)
{}

template<typename T>
ListIterator<T>& ListIterator<T>::operator++() {
	if (item == NULL) {
		item = list->first;
	}
	else {
		item = item->getNext();
	}
	return *this;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
	ListIterator<T> iter(list, item);
	if (item == NULL) {
		item = list->first;
	}
	else {
		item = item->getNext();
	}
	return iter;
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator--() {
	if (item == NULL) {
		item = list->last;
	}
	else {
		item = item->getPrevious();
	}
	return *this;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator--(int) {
	ListIterator<T> iter(list, item);
	if (item == NULL) {
		item = list->last;
	}
	else {
		item = item->getPrevious();
	}
	return iter;
}

template<typename T>
T& ListIterator<T>::operator*() {
	return item->getContent();
}

template<typename T>
bool ListIterator<T>::operator!=(const ListIterator<T>& other) const {
	return (item != other.item) || (list != other.list);
}
