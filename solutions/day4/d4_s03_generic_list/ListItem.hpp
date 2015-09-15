#ifndef LISTITEM_HPP_
#define LISTITEM_HPP_

template<class T>
class ListItem {
public:
	/** 
	 * create a list item between two elements with a given given content
	 * (also modify previous->next and next->previous)
	 */
	ListItem(ListItem<T> *prev, ListItem<T> *next, const T& content);
	/** 
	 * delete this list item (also change previous->next and next->previous
	 * to not point to this item anymore)
	 */
	~ListItem();
	T& getContent();			// get a reference to the contained data
	ListItem* getNext();		// get the next list item or NULL
	ListItem* getPrevious();	// get the previous list item or NULL
	
	ListItem<T>(const ListItem<T>& other) = delete;
	ListItem<T>& operator=(const ListItem<T>& other) = delete;
private:
	ListItem<T> *previous;		// previous item in list
	ListItem<T> *next;			// next item in list
	T content;					// content of this list item
};

#include "ListItem.tpp"

#endif /* LISTITEM_HPP_ */
