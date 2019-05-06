/***********************************************************
* Author: Giselle Northy
* Email: northyg@oregonstate.edu
* Date Created: 5/5/2019
* Filename: linkedList.c
*
* Overview:
*   This program is a linked list implementation of the deque
*	(as worked on in Worksheet 19) and bag (as worked on in
*	Worksheet 22) ADTs.
*	The deque ADT allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*	The bag ADT allows for the following behavior:
*		- adding a new link
*		- checking if a link exists with a given value
*		- removing a link  with a given value if it exists
*	Both allow for:
*		- checking if empty
*		- printing the values of all of the links
*
*	Note that both implementations utilize a linked list with
*	both a front and back sentinel and double links (links with
*	next and prev pointers).
************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%d"
#endif

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	struct Link* frontSentinel;
	struct Link* backSentinel;
	int size;
};

/**
  	Allocates the list's sentinel and sets the size to 0.
  	The sentinels' next and prev should point to eachother or NULL
  	as appropriate.
	param: 	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	list front and back sentinel not null
			front sentinel next points to back
			front sentinel prev points to null
			back sentinel prev points to front
			back sentinel next points to null
			list size is 0
 */
static void init(struct LinkedList* list) {

	/* FIXME: You will write this function */
	// From Worksheet 19
	//void LinkedListInit (struct linkedList *q)

	assert(list !=0);

	list->frontSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	// allocate back sentinel
	list->backSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->backSentinel);
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->frontSentinel->prev = 0;
	list->backSentinel->next = 0;
	list->size = 0;
}

/**
 	Adds a new link with the given value before the given link and
	increments the list's size.
 	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	list and link are not null
	post: 	newLink is not null
			newLink w/ given value is added before param link
			list size is incremented by 1
 */
static void adLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	/* _adLink places a new link BEFORE the provide link, lnk */
	//void _adLink (struct linkedList *q, struct Link *lnk, TYPE e) {
	// allocate new link
	assert(list != 0 && link != 0);
	struct Link* newLink = malloc(sizeof(struct Link));
	assert(newLink != 0);
	// set pointer connections
	newLink->prev = link->prev;
	newLink->next = link;
	newLink->prev->next = newLink;
	link->prev = newLink;
	// set new link value and increment size of list
	newLink->value = value;
	list->size++;
}

/**
	Removes the given link from the list and
	decrements the list's size.
	param: 	list 	struct LinkedList ptr
 	param:	link 	struct Link ptr
	pre: 	list and link are not null
	post: 	param link is removed from param list
			memory allocated to link is freed
			list size is decremented by 1
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// void _removeLink (struct linkedList *q, struct Link *lnk) {
	// set pointer connections

	assert(link != 0 && list != 0);

	link->next->prev = link->prev;
	link->prev->next = link->next;
	// free memory
	free(link);
	link = 0;
	// decrement size
	list->size--;

}

/**
	Allocates and initializes a list.
	pre: 	none
	post: 	memory allocated for new struct LinkedList ptr
			list init (call to init func)
	return: list
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* list = malloc(sizeof(struct LinkedList));
	init(list);
	return list;
}

/**
	Deallocates every link in the list including the sentinels,
	and frees the list itself.
	param:	list 	struct LinkedList ptr
	pre: 	list is not null
	post: 	memory allocated to each link is freed
			" " front and back sentinel " "
			" " list " "
 */
void linkedListDestroy(struct LinkedList* list)
{
	assert(list != NULL);
	while (!linkedListIsEmpty(list)) {
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
	list = NULL;
}

/**
	Adds a new link with the given value to the front of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ param value stored before current first link
			(call to adLinkBefore)
 */
void linkedListAddFront(struct LinkedList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// void LinkedListAddFront (struct linkedList *q, TYPE e)

	assert(deque != 0);

	adLinkBefore(deque, deque->frontSentinel->next, value);
}

/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created with given value before current last link
			(call to adLinkBefore)
 */
void linkedListAddBack(struct LinkedList* deque, TYPE value)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// void LinkedListAddback (struct linkedList *q, TYPE e)
	assert(deque != 0);

  adLinkBefore(deque, deque->backSentinel, value);
}

/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value
 */
TYPE linkedListFront(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// TYPE LinkedListFront (struct linkedList *q) {

	assert(deque != 0);

	assert(!linkedListIsEmpty(deque));
	return deque->frontSentinel->next->value;

}

/**
	Returns the value of the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value
 */
TYPE linkedListBack(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// TYPE LinkedListBack (struct linkedList *q) {

	assert(deque != 0);

	assert(!linkedListIsEmpty(deque));
	return deque->backSentinel->prev->value;
}

/**
	Removes the link at the front of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void linkedListRemoveFront(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// void linkedListRemoveFront (struct linkedList *q) {

	assert(deque != 0);

	assert(!linkedListIsEmpty(deque));
	removeLink(deque, deque->frontSentinel->next);
}

/**
	Removes the link at the back of the deque.
	param: 	deque 	struct LinkedList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void linkedListRemoveBack(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// void LinkedListRemoveBack (struct linkedList *q) {

	assert(deque != 0);

	assert(!linkedListIsEmpty(deque));
	removeLink(deque, deque->backSentinel->prev);
}

/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
int linkedListIsEmpty(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// From worksheet 19
	// int LinkedListIsEmpty (struct linkedList *q) {
	assert(deque != 0);

	return deque->size == 0;
}

/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct LinkedList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front
			to back; if empty, prints msg that is empty
 */
void linkedListPrint(struct LinkedList* deque)
{
	/* FIXME: You will write this function */
	// you WILL write this function!
	assert(deque != 0);
	if(deque->size == 0)
	{
		printf("Deque is empty\n");
		return;
	}

	struct Link* temp = deque->frontSentinel->next;


//temp is temporary link variable
	for(int i = 0; i < deque->size; ++i)
	{
	 printf(FORMAT_SPECIFIER"\n", temp->value);
	 temp = temp->next;
 	}
}

////////////////////////////////////////////////////////////////////////////////
//
// ON TO BAG STUFF
//
////////////////////////////////////////////////////////////////////////////////

/**
	Adds a link with the given value to the bag.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post: 	link is created w/ given value before current first link
			(call to adLinkBefore)
			Note that bag doesn't specify where new link should be added;
			can be anywhere in bag according to its ADT.
 */
void linkedListAdd(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
	// From worksheet 22
	// void linkedListAdd (struct linkedList * lst, TYPE e)
	assert(bag !=0);
  adLinkBefore(bag, bag->frontSentinel->next, value);

}

/**
	Returns 1 if a link with the value is in the bag and 0 otherwise.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	none
	ret:	1 if link with given value found; otherwise, 0
 */
int linkedListContains(struct LinkedList* bag, TYPE value)
{

	/* FIXME: You will write this function */
	// From worksheet 22
	//int linkedListContains (struct linkedList *lst, TYPE e)
assert(bag !=0);

	struct Link *current = bag->frontSentinel->next;

	while (current != bag->backSentinel)
	{
		if(EQ(current->value,value))
	      return 1;
	    current = current->next;
	}

	return 0;
}

/**
	Removes the first occurrence of a link with the given value.
	param:	bag		struct LinkedList ptr
	param: 	value 	TYPE
	pre: 	bag is not null
	post:	if link with given value found, link is removed
			(call to removeLink)
 */
void linkedListRemove(struct LinkedList* bag, TYPE value)
{
	/* FIXME: You will write this function */
	// From worksheet 22
	// void linkedListRemove (struct linkedList *lst, TYPE e) {

	assert(bag !=0);

 	struct Link *current = bag->frontSentinel->next;

		while(current != bag->backSentinel)
		{
			if(EQ(current->value,value))
			{
					removeLink(bag, current);
  		}

  		current = current->next;
		}
}
