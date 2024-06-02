#ifndef SET_H
#define SET_H 
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>



typedef struct set SET;

SET *createDataSet(int max);
void destroyDataSet(SET *sp);
void searchID(SET *sp, int id);
void insert(SET *sp, int id, int age);
void delete(SET *sp, int id);




#endif

