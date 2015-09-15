#ifndef LISTITERATOR_HPP_
#define LISTITERATOR_HPP_

class ListItem;
class List;

class ListIterator {
public:
	ListIterator(List *list, ListItem* item);			// create a new list iterator pointing to an item in a list
	int& operator*();									// get the content of the current element
	bool operator!=(const ListIterator& other) const;	// check whether this iterator is not equal to another one
	
	ListIterator& operator++();		// increment this iterator and return itself (prefix ++)
	ListIterator operator++(int);	// increment this iterator and return the previous (postfix ++)
	ListIterator& operator--();		// decrement this iterator and return itself (prefix --)
	ListIterator operator--(int);	// decrement this iterator and return the previous (postfix --)
private:
	List *list;
	ListItem *item;
};

#endif /* LISTITERATOR_HPP_ */
