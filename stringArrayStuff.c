/****************************************************************************
 * FILE: stringArrayStuff.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: it handles the creation and disposal of the array of strings
 * REFERENCE: lecture notes
 * LAST MOD: 2017-10-23
 * COMMENTS:
 *****************************************************************************/

#include "stringArrayStuff.h"
/****************************************************************************
 * NAME: listToArray
 * PURPOSE: It takes the data from the linked list and puts it into a new dinamiclly
            allocated array of equal length
 * IMPORTS: list and size, the list containing the words and the size of the list
 * EXPORTS: the new array
 * ASSERTIONS:
 *****************************************************************************/
char** listToArray(LinkedList* list, int size)
{
   int ii, len;
   char** text = (char**)malloc(sizeof(char*) * size);
   LinkedListNode *currNode = list->head;

   for(ii = 0; ii < size; ii++)
   {
      len = strlen((char*)currNode->data)+1;
      text[ii] = (char*)malloc(sizeof(char) * len);/*TODO: ask what the length should be*/
      strncpy(text[ii], (char*)currNode->data, len);
      currNode = currNode->next;
   }
   return text;

}

/****************************************************************************
 * NAME: freeArrayOfStrings
 * PURPOSE: frees an array of stings at a given size
 * IMPORTS: num, the size of the array of strings
 * EXPORTS: nothing
 * ASSERTIONS:
 *****************************************************************************/
void freeArrayOfStrings(char** text, int num)
{
   int ii;
   for (ii = 0; ii < num; ii++)
   {
      fullFree(text[ii]);
   }
   fullFree(text);
}
