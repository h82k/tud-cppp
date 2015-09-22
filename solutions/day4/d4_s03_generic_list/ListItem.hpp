#ifndef LISTITEM_HPP_
#define LISTITEM_HPP_

template<typename T>
class ListItem {
public:
	/** 
	 * create a list item between two elements with a given given content
	 * (also modify previous->next and next->previous)
	 */
	ListItem(ListItem *prev, ListItem *next, const T& content);
	/** 
	 * delete this list item (also change previous->next and next->previous
	 * to not point to this item anymore)
	 */
	~ListItem();
	T& getContent();			// get a reference to the contained data
	ListItem* getNext();		// get the next list item or NULL
	ListItem* getPrevious();	// get the previous list item or NULL
	
	ListItem(const ListItem& other) = delete;
	ListItem& operator=(const ListItem& other) = delete;
private:
	ListItem *previous;			// previous item in list
	ListItem *next;				// next item in list
	T content;					// content of this list item
};

#include "ListItem.tpp"

#endif /* LISTITEM_HPP_ */
