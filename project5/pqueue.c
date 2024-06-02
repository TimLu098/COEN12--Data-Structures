/*Yen-Jung Lu
 * COEN12 LAB5-pqueue.c
 * 11/21/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

# define start_length 10
# define p(x) (((x)-1)/2)
# define l(x) (((x)*2)+1)
# define r(x) (((x)*2)+1)

struct pqueue{
	void **data;
	int length;
	int count;
	int (*compare)();
};



//return a pointer to a new priority queue using compare as its comparison function
//Big O runtime: O(1)
PQ *createQueue(int (*compare)()) {
	PQ *pq = malloc(sizeof (PQ));
	assert(pq != NULL);
    
	pq->count = 0;
	pq->length = 10;
	pq->compare = compare;
	
	pq->data = malloc(sizeof (void *) * 10);
	
	assert(pq->data != NULL);
	return pq;
}



//deallocate memory associated with the priority queue pointed to by pq
//Big O runtime: O(1)
void destroyQueue(PQ *pq) {
	assert(pq != NULL);
	
	free(pq->data);
	free(pq);
}


//return the number of entries in the priority queue pointed to by pq
//Big O runtime: O(1)
int numEntries(PQ *pq) {
	assert(pq != NULL);
	return pq->count;
}


//add entry to the priority queue pointed to by pq
// Big O runtime: O(logn)
void addEntry(PQ *pq, void *entry) {
	assert(pq != NULL);
	
	if(pq->count == pq->length) {
		pq->length *= 2;
        	pq->data = realloc(pq->data, sizeof(void *) * pq->length);
        	assert(pq->data != NULL);
    	}	
    	pq->data[pq->count] = entry;
    	int child = pq->count;
    	int parent = (pq->count - 1) / 2;
    
	while((*pq->compare)(pq->data[child], pq->data[parent]) == -1 ) {
        	void *temp = pq->data[parent];
        	pq->data[parent] = pq->data[child];
        	pq->data[child] = temp;
        	child = parent;
        	parent = (parent - 1) / 2;
    		}
    	pq->count++;
}



// return the deleted element
// Big O runtime: O(logn)
void *removeEntry(PQ *pq) {
	assert(pq != NULL);
    	assert(pq->count > 0);
    	
	void *root = pq->data[0];
    	pq->data[0] = pq->data[pq->count-1];
    
	int minchild, parent = 0;
    	pq->count--;

	int leftchild = parent * 2 + 1;
    	int rightchild = parent * 2 + 2;


	while(parent < pq->count) {
		if(leftchild < pq->count && rightchild < pq->count) {
            		if((*pq->compare)(pq->data[leftchild], pq->data[rightchild]) == -1) {
                		minchild = leftchild;
            		}
            		else {
                	minchild = rightchild;
            		}
        	
		} 
		
		else if(leftchild < pq->count) {
            		minchild = leftchild;
        	} 
		
		else {
            		return root;
        	}
        

	if((*pq->compare)(pq->data[parent], pq->data[minchild]) == 1 ){
		void *temp = pq->data[minchild];
            	
		pq->data[minchild] = pq->data[parent];
            	
		pq->data[parent] = temp;
            	parent = minchild;
            	leftchild = parent * 2 + 1;
            	rightchild = parent * 2 + 2;
        } 
	else {
            break;
        }
    }
    return root;
}
