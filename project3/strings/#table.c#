/*Yen-Jung(Tim) Lu
 * COEN12 
 * LAB3
 * 10/24/2021
 * Description: It stores data by using the hash table
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
static int search(SET *sp, char * elt,bool *found);

struct set{   
	int count;
	int length;
	char **data;
	char  *flags; // flags for data
};


/*
 *This function provides the hashing to the string
 Big-O notation: O(1)
 */
unsigned strhash(char *s){
	unsigned hash=0;

	while(*s!='\0')
		hash=31*hash+*s++;
	return hash;
}


/*
 *This function creat the hash table
  Big-O notation: O(n)
 */
SET *createSet(int maxElts){
	SET *sp; 
	sp= malloc(sizeof(SET)); //memory allocation for SET
	assert(sp!=NULL); //assert to ensure the pointer exists

	sp-> count=0;
	sp->length= maxElts;
	
	sp->flags=malloc(sizeof(char)*maxElts); // memory allocation for flags
 	sp-> data=malloc(sizeof(char*)*maxElts);//memory allocation for data

	int i;
	for(i=0;i<sp->length; i++){
		sp->flags[i]=EMPTY;   // make every data to be empty
	}
	assert(sp->data!=NULL);
	assert(sp->flags!=NULL); //assert flags to be exists
	return sp;
}


/*
 *This function free the data point
  Big-O notation: O(n)
 */
void destroySet(SET*sp) {
	int i;
	assert(sp!=NULL); // assert to make sure pointer exists
	for(i=0;i<sp->length;i++){
		if(sp->flags[i]==FILLED){ 
			free(sp->data[i]);
		}
	}
	free(sp->flags); // free flags
	free(sp->data); // free data
	free(sp);  // free the set
		
}

/*
 *This function show the value of the element
 Big-O notation: O(1)
 */

int numElements(SET*sp){
	assert(sp!=NULL);// assert to make sure pointer exists
	return sp->count;
}



/*
 This function add elements to the set
 Big-O notation: O(1) in average case, O(n) in worst case
 */

void addElement(SET *sp, char *elt){
	assert((sp!=NULL)&&(elt!=NULL)); // assert to make sure pointers works
	int i;
	bool found;
        int location = search(sp,elt, &found);
        if(found==false){ // if search not found
                char* new = strdup(elt);
                assert(new!=NULL);   // assert "new" is valid
		sp->data[location]=new; 
		sp->flags[location]=FILLED;
                sp->count++; //increment count
        }
}


/*
 * This function remove elements 
 * Big-O notation: O(1) in average case, O(n) in worst case
 */

void removeElement(SET *sp, char *elt){
	assert(sp!=NULL); // assert to make sure pointers are valid
	assert(elt!=NULL);
	int location;
	bool found;

	location= search(sp,elt,&found); // search for the location 

	if(found){  // if found
		free(sp->data[location]); // free memory of "location"
			
		sp->flags[location]=DELETED;
		sp->count--;  // decrement count
		return;
	}
}


/*
 * This function find the element
 * Big-O notation: O(1) in average case, O(n) in worst case
 */
char *findElement(SET *sp, char *elt){

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

char **getElements(SET *sp){
        assert(sp!=NULL); // assert to make sure the pointer is valid
        char **copy;
	copy=malloc(sizeof(char *)* sp-> count);
        assert(copy!=NULL); //assert memory allocation for new pointer worked
       // return memcpy(copy,sp->data,sizeof(char *)* sp->count);
	int i;
	int j=0;
	for(i=0;i<sp->length;i++){
		if(sp->flags[i]==FILLED){
			copy[j]=sp->data[i];
			j++;
		}
	}
	return copy;
}


/*
 *This function fo the searching with the hash function with linear probing as the solution for collision
 * Big-O notation: O(1) in average case, O(n) in worst case
 */

static int search(SET *sp, char * elt,bool *found){
	assert(sp!=NULL);   // assert to the pointers
	assert(elt!=NULL);
	int i=0;
	int location;
	int delete = -1;
	int number= strhash(elt)%sp->length;  // doing the hashing
	


	while(i<sp->length){
		location=(number+i)%(sp->length);
		if(sp->flags[location]==EMPTY){
			*found=false;             // if it is empty and there is a delete, return the delete
			if(delete!=-1){
				return delete;
			}
			return location;
		}
		else if(sp->flags[location]==DELETED){
			if(delete==-1){            // if it is deleted, then return the delete as location
				delete=location;
			}
			
		}			
		else if(sp->flags[location]==FILLED){      // if it is filled, return the location that filled
			if(strcmp(sp->data[location],elt)==0){
				*found=true;
				return location;
			}	
		}
		i++;     // increment
		
		
	}
	*found=false;
	return delete;
		
					
}		






















	
