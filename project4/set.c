/* set.c
 * Yen-Jung(Tim) Lu
 * COEN12 lab4
 * 11/07/2021
 * This file implement of the set uses a hash table of generic data.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"
# include "set.h"
# define average 20


int search(SET *sp, bool *found, void *elt);

typedef struct set{
    int count;
    int length;
    LIST **lists;
    int(*compare)();
    unsigned (*hash)();
};


/*
 * This function creat the hash table
 * Runtime: O(n)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	SET *sp = malloc(sizeof(SET)); // allocate memory to pointer
	assert(sp != NULL); // assert for the pointer
	sp->compare = compare; // call the compare
	sp->count = 0;
	sp->hash = hash; // call the hash
  	sp->length=(maxElts/average);
 
	sp->lists = malloc(sizeof(LIST*)*sp->length); //allocate memory 
	int i;

	for(i = 0; i < sp->length; i++){ 
		sp->lists[i] = createList(sp->compare);
	}    

	return sp;
}


/*
 * This function free the data point
 * Runtime: O(n)
 */
void destroySet(SET*sp) {
	assert(sp!=NULL); // assert to make sure pointer exists
	
	free(sp->lists); 
	free(sp);  // free the set
	
}


/*
 * This function show the value of the element
 * Runtime: O(1)
 */

int numElements(SET*sp){
	assert(sp!=NULL);// assert to make sure pointer exists
	return sp->count;
}


/*
 * This function add elements to the set
 * Runtime: O(n)
 */
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int element= search(sp, &found, elt);//call search 
	if(found == false)
	{
		addFirst(sp->lists[element], elt);// add to front of list
		sp->count++;
    	}
}


/*
 * This function remove elements 
 * Runtime: O(n)
 */
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL); // assert to make sure pointers are valid
	assert(elt!=NULL);
	int location;
	bool found;
		

	location=search(sp,&found,elt); // search for the data location

	if(found){  // if found	
		removeItem(sp->lists[location],elt);
		sp->count--;  // decrement count
		
	}
}


/*
 * This function find the element
 * Runtime: O(n)
 */
void *findElement(SET *sp, void *elt){
	
        assert(sp!=NULL); // assert to make sure pointers are valid
        assert(elt!=NULL);
	bool found;
	int location;
        location=((*sp->hash)(elt) % sp->length);//call search
	return findItem(sp->lists[location],elt);
}


/*
 * This function make a copy of the elements
 * Runtime: O(n)
 */
void *getElements(SET *sp)
{
	assert(sp != NULL); 
	int number=0;
	
	void **copy = malloc(sizeof(void *)*(sp->count));
	int i;
	
	int size;
	void **getin;
	int numin;

	for(i = 0; i < sp->length; i++)
	{
        	getin = getItems(sp->lists[i]);
        	numin =numItems(sp->lists[i]);
		size= sizeof(numItems(sp->lists[i]));
		memcpy(copy+number,getin,numin*size);

		number+=numin;		
    	}
	return copy;       
}

   

/*
 * This function is to do the searching with the hash function 
 * Runtime: O(n^2)
*/

int search(SET *sp, bool *found, void *elt){
	assert(sp != NULL && elt != NULL);
	int i = (*sp->hash)(elt) % sp->length; 
	
	if(findItem(sp->lists[i], elt) != NULL)
	{
		*found = true;
		return i;
    }
    *found = false;
    return i;
}




