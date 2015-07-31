#ifndef LISTITERATOR_HPP_
#define LISTITERATOR_HPP_

class ListItem;
class List;

class ListIterator {
public:
	/** Create a new list iterator pointing to an item in a list */
	ListIterator(List *list, ListItem* item);

	/** increment this iterator and return itself (prefix ++) */
	ListIterator& operator++();
	
	/** increment this iterator but return previous (postfix ++) */
	ListIterator operator++(int);

	/** decrement this iterator and return itself (prefix --) */
	ListIterator& operator--();
	
	/** decrement this iterator but return previous (postfix --) */
	ListIterator operator--(int);

	/** return element content at current position. Causes runtime error if not pointing on valid list item. */
	int& operator*();

	/** check whether this iterator is not equal to an other one */
	bool operator!=(const ListIterator& other) const;

private:
	List *list;
	ListItem *item;
};

#endif /* LISTITERATOR_HPP_ */
