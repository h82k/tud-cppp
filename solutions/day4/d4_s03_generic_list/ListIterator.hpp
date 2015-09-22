#ifndef LISTITERATOR_HPP_
#define LISTITERATOR_HPP_

#include <cstdlib>

template<typename T>
class ListItem;

template<typename T>
class List;

template<typename T>
class ListIterator {
public:
	ListIterator(List<T> *list, ListItem<T>* item);		// create a new list iterator pointing to an item in a list
	T& operator*();										// get the content of the current element
	bool operator!=(const ListIterator& other) const;	// check whether this iterator is not equal to another one
	
	ListIterator& operator++();		// increment this iterator and return itself (prefix ++)
	ListIterator operator++(int);	// increment this iterator and return the previous (postfix ++)
	ListIterator& operator--();		// decrement this iterator and return itself (prefix --)
	ListIterator operator--(int);	// decrement this iterator and return the previous (postfix --)
private:
	List<T>* list;
	ListItem<T>* item;
};

#include "ListIterator.tpp"


#endif /* LISTITERATOR_HPP_ */
