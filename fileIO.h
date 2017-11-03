/****************************************************************************
 * FILE: fileIO.h
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: the header file for fileIO.h that foward declares all it's functions
 * REFERENCE: the content of this file was based on the lecture.
 * LAST MOD: 2017-10-14
 * COMMENTS: possible errors with segmental faults if inputs are too long
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FILE_READ
#define FILE_READ

#include "LinkedList.h"

#ifndef CHOICE_LENGTH
#define CHOICE_LENGTH 14 /*max number of character for a settings option*/
#endif

#ifndef MAX_WORD_LENGTH
#define MAX_WORD_LENGTH 46 /*longest word is 45, extra byte for string end*/
#endif

#ifndef MAX_FILE_NAME
#define MAX_FILE_NAME 256 /*longest possible linux fileName is 255, extra byte for string end*/
#endif

#ifndef CLEAR
#define CLEAR -28 /*the error for if a string is over 45 characters*/
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif

typedef struct {
   char dictFile[MAX_FILE_NAME];
   int maxDiff;
   int autoCorrect; /*no = 0, yes = 1*/
}Settings;

Settings* readSettings(char* fileName);
LinkedList* readWords(char* fileName);
void writeWords(char* fileName, char* text[], int size);
void nullFree(Settings** ptr);
int readWord(FILE *fp, char word[]);
char yesOrNo();
void flush();
void flushLine(FILE *fp);

#endif
