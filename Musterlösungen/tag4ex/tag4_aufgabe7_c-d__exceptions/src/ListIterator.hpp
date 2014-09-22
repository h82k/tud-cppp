/*
 * ListListIterator.hpp
 */

#ifndef LISTITERATOR_HPP_
#define LISTITERATOR_HPP_

#include <cstdlib>

template<class T>
class ListItem;

template<class T>
class List;

template<class T>
class ListIterator {
public:
	/** Create a new list iterator pointing to an item in a list */
	ListIterator(List<T> *list, ListItem<T>* item);

	/** increment this iterator and return itself (prefix ++) */
	ListIterator<T>& operator++();
	
	/** increment this iterator but return previous (postfix ++) */
	ListIterator<T> operator++(int);

	/** decrement this iterator and return itself (prefix --) */
	ListIterator<T>& operator--();
	
	/** decrement this iterator but return previous (postfix --) */
	ListIterator<T> operator--(int);

	/** return element content at current position. Causes runtime error if not pointing on valid list item. */
	T& operator*();

	/** check whether this iterator is not equal to an other one */
	bool operator!=(const ListIterator& other) const;

private:
	List<T>* list;
	ListItem<T>* item;
};


template<class T>
ListIterator<T>::ListIterator(List<T>* list, ListItem<T>* item) :
		list(list), item(item) {
}

template<class T>
ListIterator<T>& ListIterator<T>::operator++() {
	if (item == NULL)
		item = list->first;
	else
		item = item->getNext();
	return *this;
}

template<class T>
ListIterator<T> ListIterator<T>::operator++(int) {
	ListIterator<T> iter(list, item);
	if (item == NULL)
		item = list->first;
	else
		item = item->getNext();
	
	return iter;
}

template<class T>
ListIterator<T>& ListIterator<T>::operator--() {
	if (item == NULL)
		item = list->last;
	else
		item = item->getPrevious();
	return *this;
}

template<class T>
ListIterator<T> ListIterator<T>::operator--(int) {
	ListIterator<T> iter(list, item);
	if (item == NULL)
		item = list->last;
	else
		item = item->getPrevious();
	return iter;
}

template<class T>
T& ListIterator<T>::operator*() {
	return item->getContent();
}

template<class T>
bool ListIterator<T>::operator!=(const ListIterator<T>& other) const {
	return (item != other.item) || (list != other.list);
}



#endif /* LISTITERATOR_HPP_ */
