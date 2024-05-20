
//this code count the number of word in the file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define MAX_WORD_LENGTH 30

//open the file and read it
int main(int argc,char*argv[])
{

FILE *ptr = fopen(argv[1],"r");

//point out when the file can't be opened
if(ptr == NULL)
{

printf("Error, please check on the file");
exit(1);

}
int word;
char s;

word = 0;
char w[MAX_WORD_LENGTH];

// scan the file word by word 
while(fscanf(ptr,"%s",w)==1){
++word;
}
printf("total words %d",word);
}


