#include <cstddef>

class List {
public:
	List();								// create an empty list
	~List();								// delete the list and all of its elements
	List(const List &other);		// create a copy of another list
	void appendElement(int i);		// append an element to the end of the list
	void prependElement(int i);	// prepend an element to the beginning of the list
	void insertElementAt(int i, size_t pos);	// insert an element i at position pos
	size_t getSize() const;				// get the number of elements in list
	int & getNthElement(size_t n);		// get content of the n-th element.
	int & getFirst();					// get content of the first element
	int & getLast();					// get content of the last element
	int deleteFirst();			// delete first element and return it (return 0 if empty)
	int deleteLast();				// delete last element and return it (return 0 if empty)
	int deleteAt(size_t pos);		// delete element at position pos
private:
	ListItem *first, *last;		// first and last item pointers (nullptr if list is empty)
	size_t currentSize;				// current size of the list
};

#include <iostream>

/** Print the given list to the stream. N.B. list should actually be const but then we would need const ListIterators */
std::ostream &operator<<(std::ostream &stream, List &list);
