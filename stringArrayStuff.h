/****************************************************************************
 * FILE: stringArrayStuff.h
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: foward declarations of all the stringArrayStuff.c functions
 * REFERENCE: lecture notes
 * LAST MOD: 2017-10-27
 * COMMENTS:
 *****************************************************************************/

#include <stdio.h>
#include "LinkedList.h"

#ifndef STRING_ARRAY
#define STRING_ARRAY

#ifndef MAX_WORD_LENGTH
#define MAX_WORD_LENGTH 50
#endif

void freeArrayOfStrings(char** text, int num);
char** listToArray(LinkedList* list, int size);

#endif
