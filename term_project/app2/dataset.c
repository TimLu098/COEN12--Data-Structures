/* COEN12 term_project 
 *
 * Appication 2  dataset.c
 *  
 * Description: This file implement a aray to hold data
 *    
 * Date: March 13th 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2
struct set{
	int *age;
	int *flag; 
	int count; 
	int length; 
 };


/*Time Complexity: O(n)
 *  Function: Create and initialize the array*/
SET *createDataSet(int max) 
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL); 
	sp->age = malloc(sizeof(int)*max);
	sp->flag = malloc(sizeof(int)*max);
	assert(sp->age != NULL && sp->flag != NULL);
	sp->count = 0;
	sp->length = max; 
	int i;
	for(i = 0; i < sp->length; i++)
		sp->flag[i] = EMPTY;
    		return sp; 
}


/*Time Complexity: O(1)
 *  Function: Delete all elements in the array*/
void deleteDataSet(SET *sp)
{
	assert(sp != NULL);
	free(sp->age);
	free(sp->flag);
	free(sp);
	printf("\nData Set Destroyed\n\n");
}



/*Time Complexity: O(1)
 *  Function: Search in the array, to check student's record exist or not
 */
void searchID(SET *sp, int id)
{
	assert(sp != NULL);
	if(sp->flag[id] == FILLED)
        	printf("\n\nThe student with ID: %d has been found.\n", id);
    	
	else
        	printf("\n\nThe student with ID: %d could not be found.\n", id);
}



/*Time Complexity: O(1)
 *  Function: Insert new record in the array 
 */
void insert(SET *sp, int id, int age)
{
	assert(sp != NULL);
    	if(sp->flag[id] == FILLED)
    	{
        	printf("\nStudent already exists.\n");
        	return;
    	}
    	sp->age[id] = id;
    	sp->flag[id] = FILLED;
    	sp->count++;
    	printf("Inserted Student ID: %d age: %d\n", id, age);
}



/*Time Complexity: O(1)
 *  Function: Check on the record, and delete the student ID
 */
void delete(SET *sp, int id)
{
    	assert(sp != NULL);
    	if(sp->flag[id] == FILLED)
    	{
        	sp->flag[id] = EMPTY;
        	sp->age[id] = DELETED;
        	printf("\nStudent with ID: %d deleted\n", id);
        	sp->count--;
    	}
    	else
        	printf("\nStudent not found with ID: %d.\n\n", id);
}


