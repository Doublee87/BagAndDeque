#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeque.h"

/* internal functions interface */
struct DLink * _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);


/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->back is null and q->size equals zero
*/
void initCirListDeque (struct cirListDeque *q) 
{
	q->size = 0;
	q->back = 0; 
}

/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* allocate memory for the new link */
	struct DLink * lnk = (struct DLink *) malloc(sizeof(struct DLink));
   	assert(lnk != 0);
	
	lnk->value = val;
	return lnk;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	newLnk	pointer to the new link to add after the existing link
	pre:	q is not null and q is not empty
	pre: 	lnk and newLnk are not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)
{
	assert(!isEmptyCirListDeque(q));
	
	/* re-allocate pointers */
  	newLnk->next = lnk->next;
	newLnk->prev = lnk;
	lnk->next->prev = newLnk;
	lnk->next = newLnk;
	
	/* increase the size of the deque */
	q->size++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	/* create a link for the value */ 
	struct DLink * lnk = _createLink(val);
  	if (isEmptyCirListDeque(q)) 
	{
		/* if q is currently empty, the added link becomes the only link in the deque */
	  	lnk->next = lnk;
		lnk->prev = lnk;
		q->size++;		
	}
	else
	  	_addLinkAfter(q, q->back, lnk);
		
	/* change back to the newly added link */
	q->back = lnk;
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	struct DLink * lnk = _createLink(val);
	if (isEmptyCirListDeque(q))
	{
		/* if q is currently empty, the added link becomes the only link in the deque */
	  	lnk->next = lnk;
		lnk->prev = lnk;
		q->size++;
		/* change back to the newly added link */
		q->back = lnk;
	}
	else
		_addLinkAfter(q, q->back, lnk);	
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque (struct cirListDeque *q) 
{
   assert(!isEmptyCirListDeque(q));
   return q->back->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(!isEmptyCirListDeque(q));
	return q->back->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	pre:	lnk is in the deque 
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert(!isEmptyCirListDeque(q));
  	if (EQ(lnk, lnk->next))
	{
		/* if lnk is the only link in the deque, set back to null */
	  	q->back = 0;
	}
	else
	{
		lnk->next->prev = lnk->prev;
		lnk->prev->next = lnk->next;
		/* if lnk is the back link, change back to the previous of lnk */
		if (EQ(lnk, q->back))
			q->back = lnk->prev;
	}
	
	free(lnk);
	q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
   assert(!isEmptyCirListDeque(q));  	
   _removeLink(q, q->back->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	assert(!isEmptyCirListDeque(q));
	_removeLink(q, q->back);	
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	while(!isEmptyCirListDeque(q)) 
		removeBackCirListDeque(q);
	free(q);	
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	return EQ(q->size, 0);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	struct DLink *lnk;
	assert(!isEmptyCirListDeque(q));
	lnk = q->back->next;
	do
	{
		printf("%f\n", lnk->value);
		lnk = lnk->next;
	}
	while(!EQ(lnk, q->back->next));
	
	printf("+++++++++++\n");
}

/* Reverse the deque

    param:  q       pointer to the deque
    pre:    q is not null and q is not empty
    post:   the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	struct DLink *current, *next, *temp;
	assert(!isEmptyCirListDeque(q));
	next = q->back;
    do
	  {
        current = next;
        next = current->next;

        /* swap prev and next of the current link */
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
	  }
    while(!EQ(next, q->back));

	/* change the back link */
	q->back = q->back->prev;
}
