/*Yen-Jung(Tim) Lu
 * COEN12 Lab4
 * 11/07/2021
 * These codes uses a circular, doubly linked list 
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"list.h"

struct list{
        int count;
        int(*compare)();
        struct node *head;

};

struct node{
        void* data;
        struct node *next;
        struct node *prev;
};

/*
 * Runtime:O(1)
 * This function return a pointer to a new list
 */
LIST *createList(int (*compare)()){

	struct list *pList=malloc(sizeof(struct list));// allocate space for list pointer
        assert(pList!=NULL); // assert to make sure pList works

 		
 	pList->head= malloc(sizeof(struct node));// allocate for the head
        assert((pList->head)!=NULL); // assert to make sure the pointer works

	pList->count =0;

	pList->compare=compare;  
	

	pList->head->prev = pList->head; // set the dummy 
	pList->head->next = pList->head;

	return pList;
}


/*
 * Runtime:O(n)
 *This function deallocate memory associated with the list
 */
void destroyList(LIST *lp){

	assert(lp!=NULL); //assert to the pointer
	struct node *spot=lp->head; 

	while((lp->head)!=spot){
		struct	node *temp=spot; // use temporary pointer
		spot=spot->next;
		free(temp);	// deallocate it
	}

	free(lp->head);
	free(lp);
}

/*
 * Runtime:O(1)
 * This function return the count of elements
 */
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count; // return the count 

}


/*
 * Runtime:O(1)
 * This function add item as the first item in the list
 */
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL);  // assert to make sure the pointers works
	assert(item!=NULL);
	
	struct node *pNew=malloc(sizeof(struct node));// allocate memory 
	assert(pNew!=NULL);
	
	pNew->data=item;
			
	lp->head->next->prev=pNew; // make pNew before the first element
	pNew->next=lp->head->next;

	pNew->prev=lp->head;  
	
	lp->head->next=pNew;
	lp->count++;   // do the increment
	return;
}


/*
 * Runtime:O(1)
 * This funciton add item as the last item in the list
 */
void addLast(LIST *lp, void *item){
	assert(lp!=NULL); // assert to the pointer
	
	struct node *pNew=malloc(sizeof(struct node));//allocate memory
	assert(pNew!=NULL);

	pNew->data=item; 
	
	
	pNew->next=lp->head;
		
	pNew->prev=lp->head->prev;
	
	lp->head->prev->next=pNew; // make pNew to be after the last element

	lp->head->prev= pNew;
	lp->count++;
	
}


/*
 * Runtime:O(1)
 * This function remove the first item in the list
 */
void *removeFirst(LIST *lp){
	assert(lp!=NULL);
	struct node *pDel= lp->head->next;

	void *dp= pDel->data;
	lp->head->next=pDel->next; // point pDel to the first element
	pDel->next->prev=lp->head; 

	free(pDel); // delete the first element
	lp->count--;
	return dp;
}


/*
 * Runtime:O(1)
 * This function remove the last item in the list
 */
void *removeLast(LIST *lp) {

	assert(lp!=NULL&&lp->count>0); // assert to pointers
	struct node *temp = malloc(sizeof(struct node));

	temp=lp->head->prev;

	lp->head->prev=temp->prev;

	temp->prev->next=lp->head;

	lp->count--;

    	void* dataTemp=temp->data;

    	free(temp);
 	return dataTemp;
}	


/*
 * Runtime:O(1)
 * This function return the first item in the list
 */
void *getFirst(LIST *lp) {

	assert(lp!=NULL&&lp->count>0);

	return lp->head->next->data;


}

/*
 * Runtime:O(1)
 * This function return the last item in the list
 */
void *getLast(LIST *lp) {

	assert(lp!=NULL&&lp->count>0);

	return lp->head->prev->data;
}


/*
 * Runtime:O(n)
 * if item is present in the list then remove it
 */
void removeItem(LIST *lp, void *item) {


	assert(lp!=NULL&&lp->compare!=NULL);

	if(lp->count>0) {

		struct node *place=lp->head->next;

		while(place!=lp->head){


            		if((*lp->compare)(place->data,item)==0) {

                		place->prev->next=place->next;

                		place->next->prev=place->prev;
				
                		free(place);
				lp->count--;

				return;
			
            		}
		
            		place=place->next;
		
        	}
    	}
}


/*
 * Runtime:O(n)
 * This function return the data in the list
 */
void *findItem(LIST *lp, void *item){
	assert(lp!=NULL);
	assert(lp->compare!=NULL);
	struct node *place=lp->head->next;	
	int i;
	
	for(i=0; i<lp->count; i++)
	{
		if(lp->compare(item,place->data)==0)
		{
			return (place->data);
		}
		place=place->next;
	}
	return NULL;
} 


/*
 * Runtime:O(n)
 * This function return a copy of the data with array
 */
void *getItems(LIST *lp){
	assert(lp!=NULL);
	void **elts= malloc(sizeof(void*)*lp->count);

	assert(elts!=NULL);

	struct node *place=lp->head->next;

	int i=0;

	for(i=0;i<lp->count;i++){
		elts[i]= place->data;

		place= place->next;
		i++;
	
	}
	return elts;
}
