/*
 * ListItem.h
 */

#ifndef LISTITEM_H_
#define LISTITEM_H_

class ListItem {
public:
	/** 
	 * Create a list item between two elements with given content 
	 * Also modify the corresponding previous and next pointers of prev and next item
	 **/
	ListItem(ListItem *prev, ListItem *next, int content);

	/** 
	 * Delete a list item. Change also the pointers of previous and next elements to not
	 * show on this item anymore.
	**/
	~ListItem();

	/** return element content as reference */
	int& getContent();

	/** next list item, NULL if there is no next */
	ListItem* getNext();

	/** previous list item, NULL if there is no previous */
	ListItem* getPrevious();

private:
	/** previous and next items in list */
	ListItem *previous, *next;

	/** content of the list item */
	int content;
	
	/** Copy constructor in private area to forbid copying */
	ListItem(const ListItem& other);
};

#endif /* LISTITEM_H_ */
