#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <malloc.h>

/*
	initList()
	Initializes the list
	param: q the list
	pre: q is not null
	post: q size is 0
	post: Sentinels are setup with appropriate value as head, tail
*/

void initList (struct list *q) {
	assert( q != NULL ); 
	/* create the sentinels */
	q->head = (struct DLink *) malloc(sizeof(struct DLink));
	q->tail = (struct DLink *) malloc (sizeof(struct DLink));
	assert(q->head != NULL);
	assert(q->tail != NULL);

	/*Setup pointers*/
	q->head->prev = NULL;
	q->head->next = q->tail;

	q->tail->next = NULL;
	q->tail->prev = q->head;

	/*Setup values*/
	q->head->value = TYPE_SENTINEL_VALUE;
	q->tail->value = TYPE_SENTINEL_VALUE;

	q->size = 0;
}


/*
	_addLink()
		Internal function
		Adds Before the provided link, l 
	param: q the list
	param: l the  link to add before
	param: v the value to add
	pre: q is not null
	pre: l is not null
	post: q is not empty
*/

void _addLink(struct list *q, struct DLink *l, TYPE v)
{
	/*Allocate memory for new link*/
	struct DLink * lnk = (struct DLink *) malloc(sizeof(struct DLink));
	assert(lnk != 0);

	/*Setup values and pointers*/
	lnk->value = v;
	lnk->next = l;
	lnk->prev = l->prev;
	l->prev->next = lnk;
	l->prev = lnk;
	
	/*Increment size*/
	++(q->size);
}


/*
	addFrontList
	param: q the list
	param: e the element to be added
	pre: q is not null
	post: q is not empty, increased size by 1
*/

void addFrontList(struct list *q, TYPE e)
{
	_addLink(q, q->head->next, e);
}

/*
	addBackList
	param: q the list
	pre: q is not null
	post: q is not empty
*/

void addBackList(struct list *q, TYPE e) {
	_addLink(q, q->tail, e);
}

/*
	frontList
	param: q the list
	pre: q is not null
	pre: q is not empty
	post: none
*/

TYPE frontList (struct list *q) {
   assert(!isEmptyList(q));
   return q->head->next->value;
}

/*
	backList
	param: q the list
	pre: q is not null
	pre: q is not empty
	post: q is not empty
*/

TYPE backList(struct list *q)
{
	assert(!isEmptyList(q));
	return q->tail->prev->value;
}

/*
	_removeLink
	param: q the list
	param: l the linke to be removed
	pre: q is not null
	pre: l is not null
	post: q size is reduced by 1
*/

void _removeLink(struct list *q, struct DLink *l)
{
	assert(!isEmptyList(q));
	l->next->prev = l->prev;
	l->prev->next = l->next;
	free(l);
   	--(q->size);
}

void freeList(struct list *q)
{
    while(!isEmptyList(q))
    {
        removeFrontList(q);
    }
    free(q);
}

/*
	removeFrontList
	param: q the list
	pre:q is not null
	pre: q is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct list *q) {
   assert(!isEmptyList(q));
   _removeLink(q, q->head->next);
}

/*
	removeBackList
	param: q the list
	pre: q is not null
	pre:q is not empty
	post: size reduced by 1
*/

void removeBackList(struct list *q)
{
	assert(!isEmptyList(q));
	_removeLink(q, q->tail->prev);	
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *q) {
	return(q->size == 0);
}

/*	Function to print the contents of the list */

void _printList(struct list* q)
{
	struct DLink *lnk = q->head->next;
	
	while(lnk != q->tail)
	{
		printf("%f-", lnk->value);
		lnk = lnk->next;
	}
	
	printf("\n");
}

/* Recursive implementation of contains()
   Pre: current is not null
   Post: 1 if found, 0 otherwise
 */

int _contains_recursive(struct DLink* current, TYPE e){
	if( current->value == TYPE_SENTINEL_VALUE && current->next != NULL)current = current->next;
	else if( current->value == TYPE_SENTINEL_VALUE ) return 0;

	if( EQ(current->value, e) ) return 1;
	return _contains_recursive(current->next, e);
}

/* Wrapper function for contains
   Pre: lst is not null
   Post: 1 if found, 0 otherwise
*/
int listContains (struct list *lst, TYPE e) {
	assert(!isEmptyList(lst));
	return _contains_recursive(lst->head, e);
}

/* Recursive implementation of remove()*/
void _remove_recursive(struct DLink* current, TYPE e, int* sz){
	if( current->value == TYPE_SENTINEL_VALUE && current->next != NULL)current = current->next;
	else if( current->value == TYPE_SENTINEL_VALUE ) return;

	if( EQ(current->value, e) ){
	 	current->next->prev = current->prev;
		current->prev->next = current->next;
		free(current);
	   	*sz = *sz - 1;
	}
	return _remove_recursive(current->next, e, sz);
}
/* Wrapper for remove()*/
void listRemove (struct list *lst, TYPE e) {
	assert(!isEmptyList(lst));
	return _remove_recursive(lst->head, e, &(lst->size));
}
