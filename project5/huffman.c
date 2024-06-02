/*Yen-Jung Lu
  COEN12 LAB5- Huffman.c
  11/21/2021 	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"



//Big O runtime: O(1).
static struct node*makeNode(int data, struct node* left,struct  node* right) 
{
    struct  node* root = malloc(sizeof(struct node));
    assert(root != NULL);
    root->count = data;
    root->parent = NULL;
  
    if(left != NULL)
        left->parent = root;
  
    if(right != NULL)
        right->parent = root;
  
  return root;
}


//Returns the depth of node.
// Big O runtime: O(h).
static int depth(struct node* np)
{ 
    assert(np != NULL);
    if(np->parent == NULL)
        return 0;
    return depth(np->parent) + 1;
}


// compare the nodes
// Big O runtime: O(1)
static int compare(struct node *first,struct node *second)
{	
	assert(first != NULL && second!= NULL);	
	return (first->count < second->count)? -1 :(first->count > second->count);
}







// Big O runtime: O(n)
int main(int argc, char *argv[])
{
	if(argc !=3)
	{
		return 1;
	}
	FILE *fp = fopen(argv[1], "r");    

	if(fp == NULL)
        {	
		return 0;
	}

	PQ *pq = createQueue(compare);

	int n = 0;
	int count[257];
	
	int i;
	int c;
	struct node *nodes[257];

	for(i = 0; i < 257; i++){
                count[i] = 0;
                nodes[i]=NULL;
	}
	
	while((c=getc(fp))!= EOF){
        	count[c]++;
	
	}
	fclose(fp);
	


    	for(i = 0; i < 256; i++)
    	{
        	if(count[i] > 0)
        	{
            		nodes[i]= makeNode(count[i], NULL, NULL);
			addEntry(pq, nodes[i]);
        	}
    	}

	nodes[256] = makeNode(0, NULL, NULL);
    	
	addEntry(pq, nodes[256]);

 

/*While the priority queue has more than one tree in it, remove the two lowest priority trees.*/
	while(numEntries(pq) > 1)
    	{
		struct node *left = removeEntry(pq);
		struct node *right = removeEntry(pq);

			
		addEntry(pq, makeNode(left->count + right->count, left, right)); 
	
    	}


//Print out information about all the characters and call pack() 
	for(i = 0; i < 257; i++)
    	{
	
        	if(nodes[i] != NULL)
        	{
            		if(isprint(i))
            		{
               			printf("%c: %d x %d bits = %d bits\n", i,count[i], depth(nodes[i]), count[i]*depth(nodes[i]));
            		}
            		else
            		{
                 		printf("%03o: %d x %d bits = %d bits\n", i, count[i], depth(nodes[i]), count[i]*depth(nodes[i]));
            		}
        	}
    	}
	pack(argv[1], argv[2], nodes);
	return 0;
}
