/* Yen-Jung Lu
 * 
 * COEN12 LAB6
 *
 * File:        table.c
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the public and private function and type
 *              definitions for a set abstract data type for generic
 *              pointer types.  A set is an unordered collection of unique
 *              elements.
 *
 *              This implementation uses a hash table to store the
 *              elements, with linear probing to resolve collisions.
 *              Insertion, deletion, and membership checks are all average
 *              case constant time.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"

# define EMPTY   0
# define FILLED  1
# define DELETED 2

static void quicksort();
static int partition();

struct set {
    int count;                  /* number of elements in array */
    int length;                 /* length of allocated array   */
    void **data;                /* array of allocated elements */
    char *flags;                /* state of each slot in array */
    int (*compare)();		/* comparison function         */
    unsigned (*hash)();		/* hash function               */
};


/*
 * Function:    search
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Return the location of ELT in the set pointed to by SP.  If
 *		the element is present, then *FOUND is true.  If not
 *		present, then *FOUND is false.  The element is first hashed
 *		to its correct location.  Linear probing is used to examine
 *		subsequent locations.
 */

static int search(SET *sp, void *elt, bool *found)
{
    int available, i, locn, start;


    available = -1;
    start = (*sp->hash)(elt) % sp->length;  // do the hashing

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {   // if it's empty, return the index
            *found = false;
            return available != -1 ? available : locn;

        } else if (sp->flags[locn] == DELETED) { // in the case the index is deleted 
            if (available == -1)
		available = locn;

        } else if ((*sp->compare)(sp->data[locn], elt) == 0) { // compare with the compare function
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}


/*
 * Function:    createSet
 *
 * Complexity:  O(m)
 *
 * Description: Return a pointer to a new set with a maximum capacity of
 *		MAXELTS.
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp;

    assert(compare != NULL && hash != NULL); // assert compare and hash to make sure they works

    sp = malloc(sizeof(SET)); 
    assert(sp != NULL);     // assert the sp pointer

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);   // assert the sp->data

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);   // assert the sp->flag

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;  // make the whole slots to be empty

    return sp;
}


/*
 * Function:    destroySet
 *
 * Complexity:  O(m)
 *
 * Description: Deallocate memory associated with the set pointed to by SP.
 *		The elements themselves are not deallocated since we did not
 *		allocate them in the first place.  That's the rule: if you
 *		didn't allocate it, then you don't deallocate it.
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);  // assert to make sure the sp pointer works

    free(sp->flags);  // free flags
    free(sp->data);   // free data
    free(sp);         // free the set
}


/*
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Return the number of elements in the set pointed to by SP.
 */

int numElements(SET *sp)
{
    assert(sp != NULL);    // assert to the sp
    return sp->count;      // return the count
}


/*
 * Function:    addElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Add ELT to the set pointed to by SP.
 */

void addElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL); // assert to the sp and elt
    locn = search(sp, elt, &found);    // assign the value for the locn

    if (!found) {
	assert(sp->count < sp->length);  // assert to make sure count is less than the length

	sp->data[locn] = elt;     // allocate memory if the word hasn't present yet
	sp->flags[locn] = FILLED; 
  	sp->count ++;     // increment the count
    }
}


/*
 * Function:    removeElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Remove ELT from the set pointed to by SP.  A element is
 *		deleted by changing the state of its slot.
 */

void removeElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);  // assert to the sp and elt
    locn = search(sp, elt, &found);    // assign the value for the locn

    if (found) {                // if it is found
	sp->flags[locn] = DELETED;   
	sp->count --;
    }
}


/*
 * Function:    findElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: If ELT is present in the set pointed to by SP then return
 *		it, otherwise return NULL.
 */

void *findElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);  // assert to the sp and elt

    locn = search(sp, elt, &found);     // assign the value for locn
    return found ? sp->data[locn] : NULL;  // return NULL when we can't found
}


/*
 * Function:	getElements
 *
 * Complexity:	O(m)
 *
 * Description:	Allocate and return an array of elements in the set pointed
 *		to by SP.
 */

void *getElements(SET *sp)
{
    	int i, j;
    	void **elts;

    	assert(sp != NULL);   // assert to the sp

   	elts = malloc(sizeof(void *) * sp->count);
    	assert(elts != NULL);

	for (i = 0, j = 0; i < sp->length; i ++){
		if (sp->flags[i] == FILLED){
	    		elts[j ++] = sp->data[i];
		}
	}
	
	quicksort(sp, elts, 0, sp->count-1);   // use quicksort to sort the new array
	return elts;
}


//Function: partition
//
//Complexity: O(n)
//
//Description: sort array to make the left to be smaller and the right to be bigger
static int partition(SET *sp,void** elts, int lo, int hi){
	
	assert(sp!=NULL); // assert to make sure the pointer works

	int smallNum = lo - 1; 	// the index for the smaller number 
	void *pivot= elts[hi];  // make pivot have the value of the rightmost element
		
	int i;
	for (i=lo; i <= hi - 1; i++){ 
		if ((*sp->compare)(elts[i], pivot) <= 0){  // compare the pivot with the selected element
			smallNum++;  // increment the smaller number 

			void* temp = elts[smallNum];  
			elts[smallNum] = elts[i];

	
			elts[i] = temp;
    		
  		}
	}
  		void*change  = elts[smallNum + 1]; // change the spot of the next element of the smallernum
  		elts[smallNum + 1] = elts[hi];
		elts[hi]=change;
	
  	return smallNum + 1;   // return the next element of the smallerNum
	
}


//
//Function: quicksort
//
//COmplexity:O(nlogn) for the average, and  O(n^2) for the worst 
//
//Description: recursive function to sort the subarrays to the left and right of pivot
static void quicksort(SET *sp,void** elts, int lo, int hi){
	assert(sp != NULL); // assert to make sure the pointer works
  	if(lo < hi){
    	
		int partitionNum = partition(sp, elts, lo, hi);

    		quicksort(sp, elts, lo, partitionNum - 1); // the left side
    		quicksort(sp, elts, partitionNum + 1, hi); // the right side
  	}
  	
	return;
}


