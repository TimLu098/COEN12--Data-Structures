/*
 * Yen-Jung Lu
 * COEN12 term_project
 * APP3 dataset.c
 * Description:  Use Circular doubly linked list to perform the third scenerio.
 *
 * Date: March 13th 2022
 *
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"


 
struct record
{
	int ID;	
	int Age;			
};


struct list
{
	int count;
	struct node*head;

};


struct node
{

	struct node *next;

	struct node *prev;

	RECORD record;; 
};




//Time Complexity: O(1)
//Function: Allocate memory for the data set. A dummy node is created, and have the next and prev pointers pointing to it.

LIST *createDataSet()
{	
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL); 
	lp->count = 0;	
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}



//Time Complexity: O(n)
//FUnction: Destroy memory that was allocated from createDataSet 

void destroyDataSet(LIST *lp)
{
        assert(lp != NULL);
        NODE *pDel;
        NODE *pPrev = lp->head->prev;
        do
        {
                pDel = pPrev;
                pPrev = pDel -> prev;
                free(pDel);
        }
        while (pDel != lp->head);
                free(lp);
}


//Time Complexity: O(n)
//Function: Using sequential search to search through the list to find whether the student's age exist or not.
void searchAge(LIST *lp, int studentAge)
{
	assert(lp != NULL);
	if(lp->count == 0)
	{
		printf("No records in the Data Set, cannot execute search.\n");
		return;
	}
	printf("Searching for record with Age %d \n",studentAge);
	NODE *pLoc = lp->head->next;
	while(pLoc != lp->head)
	{
		if(pLoc->record.Age == studentAge)
			{
				printf("Record with Age %d was found\n",pLoc->record.Age);
				return;
			}
		else
			{
				pLoc = pLoc->next;
			}
	}
	printf("Student with that Age was not found.\n");
}



//Time Complexity: O(n)
//Function: Use sequential search to through the list to check whether student's ID exist in the list or not.
void searchID(LIST *lp, int studentID)
{
	assert(lp != NULL);
	if(lp->count == 0)
	{
		printf("No records in the Data Set, cannot execute search.\n");
		return;
	}	printf("Searching for record with ID %d.\n",studentID);
	printf("Searching for record with ID %d.\n",studentID);
	NODE *pLoc = lp->head->next;
	while(pLoc != lp->head)
		{
			if(pLoc->record.ID == studentID)
				{
					printf("Record with ID %d was found\n",pLoc->record.ID);
					return;
				}
			else
				{
					pLoc= pLoc->next;
				}
		}
	printf("Student with that ID was not found\n");
}





//Time Complexity: O(n)
//Function: Use sequential search to find the correct space to insert a node with the given age and ID number. 
void insertion(LIST *lp, int studentAge, int studentID)
{
	assert(lp != NULL);
	NODE *pNew = malloc(sizeof(struct node));
	assert(pNew != NULL);
	NODE *pLoc = lp->head->next;

	while(pLoc != lp->head)
	{
		if(pLoc->record.Age < studentAge)
		{
			pLoc = pLoc->next;
		}
		else
		{
			break;
		}
	}
	pNew->record.Age = studentAge;
	pNew->record.ID = studentID;
	pNew->next = pLoc;
	pNew->prev = pLoc->prev;
	pLoc->prev->next = pNew;
	pLoc->prev = pNew;
	lp->count++;
}


//Time Complexity: O(n)
//Function: Use sequential search to find the specific node with the same ID number as the parameter. The searched value will be deleted afterward. 
void deletion(LIST *lp, int studentID)
{
	assert (lp != NULL);
	assert(lp->count > 0);
	printf("Searching for and removing record with ID %d \n",studentID);
	NODE *pDel = lp->head->next;
	



	while(pDel != lp->head)
	{
		if(pDel->record.ID == studentID)
		{
			int tempID = pDel->record.ID;

			pDel->prev->next = pDel->next;
			pDel->next->prev = pDel->prev;
			free(pDel);
			lp->count--;
			printf("Record with ID %d has been located and removed.\n", tempID);
			return;	
		}
		else
		{
			pDel = pDel->next;
		}
	}
	if(pDel->record.ID != studentID)
	{	
		printf("Record with ID %d could not be located and removed.\n",studentID);
		return ;
	} 
}


//Time Complexity: O(1)
//FUnction: Return the maximum age difference of all students. We can find the gap by subtract the beginning of the list by the end of out list 
int maxAgeGap(LIST *lp)
{
	assert(lp != NULL);
	assert(lp->count > 1);
	return lp->head->prev->record.Age - lp->head->next->record.Age;
}
