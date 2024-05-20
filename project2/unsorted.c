/*
Yen-Jung(Tim) Lu
COEN12 Lab2
Use sequential search to locate an element in the array
*/
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include"set.h"
struct set{   
	int count; // number of elements
	int length;  // length of array
	char **data;  // showing the string within array

};

// return the location of the element when search
// Time: O(n)
 static int search(SET *sp, char * elt){
 	int i;
 	for(i=0; i<sp->count; i++){
 		if (strcmp(sp->data[i],elt)==0)
			return i;
	}
	return -1; // return -1 if not found
}            


// Create a new set
// Time: O(n)
SET*createSet(int maxElts){
	SET *sp; 
	sp= malloc(sizeof(SET)); //memory allocation for SET
	assert(sp!= NULL); //assert to ensure the pointer exists

	sp-> count=0;
	sp->length= maxElts;
	sp-> data=malloc(sizeof(char*)*maxElts); // memory allocation for the data
 
	assert(sp->data!=NULL); //assert data to be exists
	return sp; 

}

// destroy a set
// Time: O(n)
void destroySet(SET*sp) {
	int i;
	assert(sp!=NULL); // assert to make sure pointer exists
	for(i=0;i<sp->count;i++) 
		free(sp->data[i]); // free data
		free(sp->data); // free array
		free(sp);  // free the set
}

// Count the number of elements in the set
// Time: O(n)
int numElements(SET*sp){
	assert(sp!=NULL);// assert to make sure pointer exists
	return sp->count;  
}

// Add element to set
// Time: O(n)
void addElement(SET *sp, char *elt){ 
  	assert((sp!=NULL)&&(elt!=NULL)); // assert to make sure pointers works
	int target = search(sp,elt); 
	if(target==-1){ // if search not found
   		assert(sp->length>sp->count); // assert count less than length
		char* new = strdup(elt); 
		assert(new!=NULL);   // assert "new" is valid
		sp->data[sp->count]=new;  

		sp->count++; //increment count
	}
}


// Remove an element in the set
// Time: O(n)
void removeElement(SET *sp, char *elt){ 
	assert(sp!=NULL); // assert to make sure pointers are valid
	assert(elt!=NULL);
	int location;
	int i;

	location= search(sp,elt);

	if(location!=-1){  // if search not found
		free(sp->data[location]); // free memory of "location"
		for(i=location+1;i<sp->count;i++) 
			sp->data[i-1]= sp->data[i];   
			sp->count--;  // decrement count
	}
}

// Find element in the set
// Time: O(n)
char *findElement(SET *sp, char *elt){
	assert(sp!=NULL); // assert to make sure pointers are valid
	assert(elt!=NULL);
	int location;
 
	location= search(sp,elt);
	if(location==-1){   // if the search not found return NULL
		return NULL;
	}
	return sp->data[location]; // return the element
}


//Allocate and return an array of elements in the set pointed to by pointer
//Time: O(n)
char **getElements(SET *sp){
	assert(sp!=NULL); // assert to make sure the pointer is valid
	char **copy;// declare new pointer points to pointers
	copy=malloc(sizeof(char *)* sp-> count);
	assert(copy!=NULL); //assert memory allocation for new pointer worked
	return memcpy(copy,sp->data,sizeof(char *)* sp->count);
}


