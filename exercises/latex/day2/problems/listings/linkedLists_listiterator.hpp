class ListIterator {
public:
	// create a new list iterator pointing to an item in a list
	ListIterator(List *list, ListItem *item);
	// get the content of the current element
	int& operator*();
	// check whether this iterator is not equal to another one
	bool operator!=(const ListIterator &other) const;
private:
	List *list;
	ListItem *item;
};
