/**
 * This example demonstrates how to implement a "generic" list in C.
 *
 * The basic idea is to use a void pointer for referencing the content.
 * Since the user knows the type of the elements in the list, he can
 * cast the pointer to the correct type when reading content from the
 * list.
 *
 * In contrast to C++, this list implementation may hold items of
 * different types, e.g., strings/const char* and unsigned ints.
 */
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
	struct ListElement* next;
	struct ListElement* prev;

	void* content;
};

struct List {
 struct ListElement* firstElement;
};


int main(int argc, char **argv) {
	// Initialize first list element
	struct ListElement firstElement;
	firstElement.content = "some string";
	firstElement.next = NULL;

	// Initialize second list element
	unsigned int anInteger = 3;
	struct ListElement secondElement;
	secondElement.content = &anInteger;
	firstElement.next = &secondElement;
	secondElement.next = NULL;

	// Build list
	struct List list;
	list.firstElement = &firstElement;

	// Fetch list elements
	printf("First element's address: 0x%p\n", list.firstElement);
	printf("First element's content: '%s'\n", (const char*)list.firstElement->content);
	printf("First element's successor: 0x%p\n", list.firstElement->next);

	printf("--- \n");

	printf("Second element's address: 0x%p\n", list.firstElement->next);
	printf("Second element's content: '%d'\n", *((unsigned int*)list.firstElement->next->content));
	printf("Second element's successor: 0x%p\n", list.firstElement->next->next);

	return 0;
}
