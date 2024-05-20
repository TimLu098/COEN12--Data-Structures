/*
Yen-Jung(Tim) Lu
COEN12 Lab2
Use binary search to locate an element in the array
*/
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include"set.h"

static int search(SET *sp, char * elt,bool *found);

struct set{   //other set will be capitalized
	int count;
	int length;
	char **data;
};



// Create a new set
// Time: O(n)
SET*createSet(int maxElts){
	SET *sp; 
	sp= malloc(sizeof(SET)); //memory allocation for SET
	assert(sp!=NULL); //assert to ensure the pointer exists

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
	int i;
	bool found;
        int target = search(sp,elt, &found);
        if(found==false){ // if search not found
                assert(sp->length>sp->count); // assert count less than length
                char* new = strdup(elt);
                assert(new!=NULL);   // assert "new" is valid
                
		for(i=sp->count;i>target;i--){
			sp->data[i] = sp->data[i-1]; // shifting
		}
			
		sp->data[target]=new; 
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
	bool found;

	location= search(sp,elt,&found);

	if(found){  // if search not found
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
	bool found;
        location= search(sp,elt,&found);
        if(found==false){   // if the search not found return NULL
                return NULL;
        }
        return sp->data[location]; // return the element
}

// Allocate and return an array of elements in the set pointed to by pointer
// Time: O(n)
char **getElements(SET *sp){
        assert(sp!=NULL); // assert to make sure the pointer is valid
        char **copy;
	// declare new pointer points to pointers
        copy=malloc(sizeof(char *)* sp-> count);
        assert(copy!=NULL); //assert memory allocation for new pointer worked
        return memcpy(copy,sp->data,sizeof(char *)* sp->count);
}





//Binary search funcitons
//Time:O(logn)
static int search(SET *sp, char * elt,bool *found){
	int lo,hi,mid;
	lo=0;
	hi=sp->count-1;
	while(lo<= hi){ 
		mid=(lo+hi)/2;

		if(sp->data[mid]== elt){
		found==true;
		break;
		}

		else if(sp->data[mid]>elt){
		hi=mid-1;
		}

		else{
		lo=mid+1;
		}
	}
	
}


