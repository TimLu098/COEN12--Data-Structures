/*
 * File:        set.h
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for generic
 *              pointer types.  A set is an unordered collection of
 *              distinct elements.
 */

# ifndef SET_H
# define SET_H

typedef struct set SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());

void destroySet(SET *sp);

int numElements(SET *sp);

void addElement(SET *sp, void *elt);

void removeElement(SET *sp, void *elt);

void *findElement(SET *sp, void *elt);

void *getElements(SET *sp);

static int partition(SET *sp,void** elts, int lo, int hi);

static void quicksort(SET *sp,void** elts, int lo, int hi);

# endif /* SET_H */
