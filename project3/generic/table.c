/*Yen-Jung Lu
  COEN12 LAB3 
  10/20/2021
  Description: this code implement the hash table with generic pointers
*/
 

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include"set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2
static int search(SET *sp, void * elt,bool *found);


struct set{   
	int count;      
	int length;     // the whole length of the set
	void **data;
	char  *flags;    // flage the data
	int(*compare)();  // the replacement of strcmp
	unsigned(*hash)();  // the replacement of strhash
};



/*
 * This function creat the hash table
 * Big-O notation: O(n)
 */

SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)()){
	SET *sp; 
	sp= malloc(sizeof(SET)); //memory allocation for SET
	assert(sp!=NULL); //assert to ensure the pointer exists

	sp-> count=0;
	sp->length= maxElts;
	
	sp->flags=malloc(sizeof(char)*maxElts); // memory allocation for flag
 	sp-> data=malloc(sizeof(void*)*maxElts); // memory allocation for data
	sp->compare=compare;
	sp->hash=hash;
	int i;
	for(i=0;i<sp->length; i++){
		sp->flags[i]=EMPTY;
	}
	assert(sp->data!=NULL);
	assert(sp->flags!=NULL); //assert flags to be exists
	return sp;
}

/*
 * This function free the data point
 * Big-O notation: O(1)
 */

void destroySet(SET*sp) {
	assert(sp!=NULL); // assert to make sure pointer exists
	
	free(sp->flags); // free flags
	free(sp->data); // free data
	free(sp);  // free the set
	
}



/*
 * This function show the value of the element
 * Big-O notation: O(1)
 */

int numElements(SET*sp){
	assert(sp!=NULL);// assert to make sure pointer exists
	return sp->count;
}



/*
 * This function add elements to the set
 * Big-O notation: O(1) in average case, O(n) in worst case
 */
void addElement(SET *sp, void *elt){
	assert((sp!=NULL)&&(elt!=NULL)); // assert to make sure pointers works
	bool found;
        int location = search(sp,elt, &found);// use search to locate the spot	

        if(found==false){ // if search not found
		sp->data[location]=elt; 
		sp->flags[location]=FILLED;
                sp->count++; //increment count
        }
}


/*
 * This function remove elements 
 * Big-O notation: O(1) in average case, O(n) in worst case
 */
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL); // assert to make sure pointers are valid
	assert(elt!=NULL);
	int location;
	bool found;

	location= search(sp,elt,&found);// search for the data location

	if(found){  // if found	
		sp->flags[location]=DELETED;
		sp->count--;  // decrement count
		
	}
}


/*
 * This function find the element
 * Big-O notation: O(1) in average case, O(n) in worst case
 */

void *findElement(SET *sp, void *elt){

        assert(sp!=NULL); // assert to make sure pointers are valid
        assert(elt!=NULL);
        int location;
	bool found;
        location= search(sp,elt,&found);
        if(found==false){   // if the search not found return NULL
                return NULL;
        }
        else{
		 return sp->data[location]; // return the element
	}
}


/*
 * This function make a copy of the elements
 * Big-O notation: O(n)
 */
void *getElements(SET *sp){
        assert(sp!=NULL); // assert to make sure the pointer is valid
        void **copy;
	copy=malloc(sizeof(void *)* sp-> count);
        assert(copy!=NULL); //assert memory allocation for new pointer worked
	int i;
	int j=0;              // j represent the inital spot of the data
	for(i=0;i<sp->length;i++){
		if(sp->flags[i]==FILLED){
			copy[j]=sp->data[i];  // put the data to j
			j++;
		}
	}
	return copy;
}



/*
 * This function fo the searching with the hash function with linear probing as the solution for collision
 *
* Big-O notation: O(1) in average case, O(n) in worst case
*/


static int search(SET *sp, void * elt,bool *found){
	assert(sp!=NULL);     // assert to the pointers
	assert(elt!=NULL);   
	int i=0;
	int location;
	int delete = -1;
	int number= ((*sp->hash)(elt))%sp->length; // assigned number to do hash
	
	

	while(i<sp->length){
		location=(number + i)%(sp->length);

		if(sp->flags[location]==EMPTY){ // if it is empty and there is a delete, return the delete

			*found=false;
			if(delete!=-1){
				return delete;
			}
			return location;
		}
		else if(sp->flags[location]==DELETED){  // if it is deleted, then return the delete as location
			if(delete==-1){
				delete=location;
			}
			
		}			
		else if(sp->flags[location]==FILLED){
			if((*sp->compare)(sp->data[location],elt)==0){  // // if it is filled, return the location that filled
				*found=true;
				return location;
			}	
		}
		i++;
	}
	*found=false;
        return delete;
					
}		






















	
