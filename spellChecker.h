/****************************************************************************
 * FILE: spellChecker.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: foward declarations of spellChecker.c
 * REFERENCE: UCP lecture notes
 * LAST MOD: 2017-10-27
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SPELLCHECK
#define SPELLCHECK

#include "check.h"
#include "fileIO.h"
#include "stringArrayStuff.h"

void spellChecker(char* fileName);
void displayArray(char* words[], int size);
int callBack(char* word, char* suggestion);
int autoCallBack(char* word, char* suggestion);

#endif
