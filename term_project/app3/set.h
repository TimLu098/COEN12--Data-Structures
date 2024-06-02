#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <assert.h>

# ifndef SET_H
# define SET_H

typedef struct record RECORD;

typedef struct list LIST;

typedef struct node NODE;

LIST* createDataSet();

void searchAge(LIST*,int);

void searchID(LIST*,int);

void destroyDataSet(LIST*);

void insertion(LIST*,int,int);

void deletion(LIST*,int);

int maxAgeGap(LIST*);

# endif 
