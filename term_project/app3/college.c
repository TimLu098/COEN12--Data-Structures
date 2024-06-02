/* 
 * Yen-Jung Lu
 *
 * COEN12 term_project
 *
 * APP3 college.c
 *
 * Desciption: College.c include the main function to testing a list abstract abstract datatype.
 *
 * Date: March 13th 2022
 *
 */




# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>
# include "set.h"


struct record
{
	int ID;
	int Age;
};
    
struct list
{	 
	int count;
	struct node *head;
};

struct node
{
	struct node *next;
	struct node *prev;
	RECORD record;
}; 


// This program create a sorted circular doubly linked list and insert 100 student records into
// list with random ID ranging from 1 to 2000 and Age ranging from 18 to 30 years olds.  
int main()
{
	LIST* list;
	list = createDataSet();
	printf("Data Set Created\n");
	srand ((int) time (NULL)); //initialize rand
	
 
	int previousID = 0; 



	int i;
	for(i = 0; i <1000; i++)    // insert 100 records in the list
		{
			int studentAge = rand()%(13) +18;  //the range is from 18 to 30
		

			int ID = rand()%2 + 1;              //the range is varying from 1 to 2000 
			previousID = previousID + ID;
	
			insertion(list,studentAge,previousID);
		

	printf("Inserted student ID: %d, Age: %d\n", previousID, studentAge);

	}
	printf("All records are inserted\n");

	int testID = rand()%(1999)+1;  //  the ID range from 1 to 2000
	int testAge = rand()%(13)+18;  // the Age range from 18 to 30
	searchID(list,testID);
	searchAge(list,testAge);
	int removeID = rand()%(1999)+1;
	deletion(list,removeID);

	int AgeGap = maxAgeGap(list);
        printf("The maximum age gap is %d\n",AgeGap); 
	
	printf(" Data Set destroyed\n");
	destroyDataSet(list);	
}
