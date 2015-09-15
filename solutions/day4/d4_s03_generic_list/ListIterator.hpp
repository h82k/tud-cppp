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
	ListIterator(List<T> *list, ListItem<T>* item);		// create a new list iterator pointing to an item in a list
	T& operator*();										// get the content of the current element
	bool operator!=(const ListIterator& other) const;	// check whether this iterator is not equal to another one
	
	ListIterator<T>& operator++();		// increment this iterator and return itself (prefix ++)
	ListIterator<T> operator++(int);	// increment this iterator and return the previous (postfix ++)
	ListIterator<T>& operator--();		// decrement this iterator and return itself (prefix --)
	ListIterator<T> operator--(int);	// decrement this iterator and return the previous (postfix --)
private:
	List<T>* list;
	ListItem<T>* item;
};

#include "ListIterator.tpp"


#endif /* LISTITERATOR_HPP_ */
