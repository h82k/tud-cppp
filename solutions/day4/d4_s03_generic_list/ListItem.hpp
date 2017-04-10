#ifndef LISTITEM_HPP_
#define LISTITEM_HPP_

template<typename T>
class ListItem {
public:
	/** 
     * @name ListItem*ListItem *prev, ListItem *next, int content);
     * @brief constructor of a listitem
     * @author cppp
     * @param *prev pointer to the previous listitem (null if none)
     * @param *next pointer to the next listitem (null if none)
     * @param content the content hold by the listitem
	 * create a list item between two elements with a given given content
	 * (also modify previous->next and next->previous)
	 */
	ListItem(ListItem *prev, ListItem *next, const T& content);
	/** 
     * @name ~ListItem();
     * @brief destructor of listitem
     * @author cppp
	 * deletes the listitem object and, if possible, links together the 
     * previous and next listitem
	 */
	~ListItem();

	/** 
     * @name getContent();
     * @brief returns the content of the listitem
     * @author cppp
     * @return a T reference
	 */
	T& getContent();			// get a reference to the contained data
	/** 
     * @name getNext();
     * @brief returns the next listitem
     * @author cppp
     * @return the next listitem
	 */
	ListItem* getNext();		// get the next list item or NULL
	/** 
     * @name getPrevious();
     * @brief returns the previous listitem
     * @author cppp
     * @return the previous listitem
	 */
	ListItem* getPrevious();	// get the previous list item or NULL
	
	/** 
     * @name ListItem(const ListItem& other) = delete;
     * @brief disables the copy constructor
     * @author cppp
	 */
	ListItem(const ListItem& other) = delete;
	/** 
     * @name operator=(const ListItem& other) = delete;
     * @brief disables the = operator
     * @author cppp
	 */
	ListItem& operator=(const ListItem& other) = delete;
private:
	ListItem *previous;			// previous item in list
	ListItem *next;				// next item in list
	T content;					// content of this list item
};

#include "ListItem.tpp"

#endif /* LISTITEM_HPP_ */
