/* 
 * Yen-JUng LU
 *
 * COEN12 Term_project
 *
 * Application2 college.c
 *
 * Desricption: include the main function that will generate student record and test the dataset 
 *
 * Date: March 13th 2022 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "set.h"

#define MAX_STUDENTS 3000


int main()
{
	srand(time(NULL));

    	SET *sp = createDataSet(MAX_STUDENTS);

    	int i, id, age, first; 
    	int prevID = 0;


	for(i = 0; i < 1000; i++)   // generate 100 random students
    	{
        	first = (rand() % 2)+1;
        	id = prevID + first;
        	prevID = id;
        	age = (rand() % (13)+18); 
        	insert(sp, id, age);
    	}
	
	int pID = (rand() % (2000)+1);   // generate a random student, search and delete it

    	searchID(sp, pID);

    	delete(sp, pID);

    	deleteDataSet(sp);

    	return 1;
}

