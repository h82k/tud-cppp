#ifndef LISTITEM_HPP_
#define LISTITEM_HPP_

template<class T>
class ListItem {
public:
	/** 
	 * Create a list item between two elements with given content 
	 * Also modify the corresponding previous and next pointers of prev and next item
	 **/
	ListItem(ListItem<T> *prev, ListItem<T> *next, const T& content);

	/** 
	 * Delete a list item. Change also the pointers of previous and next elements to not
	 * show on this item anymore.
	**/
	~ListItem();

	/** return element content as reference */
	T& getContent();

	/** next list item, NULL if there is no next */
	ListItem* getNext();

	/** previous list item, NULL if there is no previous */
	ListItem* getPrevious();
private:
	/** previous and next items in list */
	ListItem<T> *previous, *next;

	/** content of the list item */
	T content;
	
	/** Copy constructor in private area to forbid copying. No implementation! */
	ListItem<T>(const ListItem<T>& other);
};

#include "ListItem.tpp"

#endif /* LISTITEM_HPP_ */
