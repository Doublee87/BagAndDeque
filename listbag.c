#include "listbag.h"
#include <assert.h>
#include "type.h"
#include <malloc.h>

/*Bag interface*/

/*Initialize the bag*/
void initBag(struct bag* b){
	assert( b != NULL);
	b->l = (struct list*)malloc(sizeof(struct list));/*Allocate for the list implementing the bag*/
	initList(b->l);/*Initialize list*/
}

void addToBag(struct bag* b, TYPE val){
	addFrontList(b->l, val);
}

void removeFromBag(struct bag* b, TYPE val){
	listRemove(b->l, val);
}

/* Bag contains()
   Just calls listContains() */
int bagContains(struct bag* b, TYPE val){
	return listContains(b->l, val);
}

/* Test for empty bag
   Pre: b is not null
*/
int isEmptyBag(struct bag* b){
	return isEmptyList(b->l);
}

void freeBag(struct bag *b)
{
    assert(b != NULL);
    freeList(b->l);
    free(b);
}

