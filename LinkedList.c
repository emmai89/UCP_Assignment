/****************************************************************************
 * FILE: LinkedList.c
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: Create a list and manipulate the data inside of it
 * REFERENCE: lecture notes and previous practicals
 * LAST MOD: 2017-10-14
 * COMMENTS: Iterative functions were used in place of recursive because the
             large size of the dictionary file was causing stack overflow
 *****************************************************************************/

#include "LinkedList.h"

/****************************************************************************
 * NAME: enptyList
 * PURPOSE: Create an empty linked list
 * IMPORTS: nothing
 * EXPORTS: an empty linked list
 * ASSERTIONS:
 *****************************************************************************/
LinkedList* emptyList()
{
   LinkedList *list;
   list = (LinkedList*)malloc(sizeof(LinkedList));
   list->head = NULL;
   list->tail = NULL;
   list->length = 0;
   return list;
}

/****************************************************************************
* NAME: insertFirst
* PURPOSE: Insert an element at the front of
*          the list
* IMPORTS: list and entry, the linked list been
*          altered and the value that is to be
*          added
* EXPORTS: nothing, but it list passed in is
*          altered
* ASSERTIONS:
****************************************************************************/
void insertFirst(LinkedList *list, void* entry)
{
   LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
   newNode->data = entry;

   if(list->head == NULL)
   {
      list->head = newNode;
      list->tail = newNode;
      newNode->next = NULL;
   }
   else
   {
      newNode->next = list->head;
      list->head = newNode;
   }

   list->length++;
}

/****************************************************************************
 * NAME: insertLast
 * PURPOSE: Insert an element at the end of the list
 * IMPORTS: list and entry, the linked list been altered and the value that is
           to be added
 * EXPORTS: nothing, but it list passed in is altered
 * ASSERTIONS:
 *****************************************************************************/
void insertLast(LinkedList *list, void* entry)
{
   LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
   newNode->data = entry;
   newNode->next = NULL;

   if(list->head == NULL)
   {
      list->head = newNode;
      list->tail = newNode;
   }
   else
   {
      list->tail->next = newNode;
      list->tail = newNode;
   }
   list->length++;
}

/*****************************************************************************
 * NAME: removeFirst
 * PURPOSE: Remove the element at the front of the list
 * IMPORTS: list, the linked list been altered
 * EXPORTS: the value been removed from the list
 * ASSERTIONS:
 ******************************************************************************/
void* removeFirst(LinkedList *list)
{
   LinkedListNode *temp = NULL;
   void* data;
   if(list->head != NULL)
   {
      temp = list->head;
      list->head = list->head->next;
      data = temp->data;
      fullFree(temp->data);
      fullFree(temp);
      list->length--;
   }

   return data;
}

/******************************************************************************
* NAME: find
* PURPOSE: finds the value at the n-th point of of the linked list
* IMPORTS: num and list, the position of the value in the list and linked list
           that is been searched
* EXPORTS: the value that is found
* ASSERTIONS:
******************************************************************************/
void* find(int num, LinkedList *list)
{
   void *j = NULL;

   if(list->length > num)
   {
      j = (void*)(findRec(num, list->head)->data);
   }

   return j;
}

/******************************************************************************
* NAME: findRec
* PURPOSE: A recursive fuction that traveses throught the list until num is 0
* IMPORTS: num and list node, the number of resussions left and the current
*          node in the linked list
* EXPORTS: the current node
* ASSERTIONS:
******************************************************************************/
LinkedListNode* findRec(int num, LinkedListNode* node)
{
   if(num != 0)
   {
      node = findRec((num-1), node->next);
   }
   return node;
}

/******************************************************************************
* NAME: display
* PURPOSE: an iterative fuction that displays the value at each node of the list
*          to the terminal, until it reaches the end
* IMPORTS: list, the linked list to be displayed
* EXPORTS: nothing, but it just displays to the terminal
* ASSERTIONS:
******************************************************************************/
void display(LinkedList* list)
{
   LinkedListNode *node = list->head;
   while(node != NULL)
   {
      printf("%s\n", (char*)node->data);
      node = node->next;
   }
}

/******************************************************************************
* NAME: freeLinkedList
* PURPOSE: it frees all malloc'd data in the linked list
* IMPORTS: list, the list to be freed
* EXPORTS: nothing
* ASSERTIONS:
******************************************************************************/
void freeLinkedList(LinkedList* list)
{
   freeNode(list->head);
   fullFree(list);
}

/******************************************************************************
* NAME: freeNode
* PURPOSE: a iterative fuction that free all the nodes, and their values, in
*          the link list
* IMPORTS: head, the head of the list, where the freeing begins
* EXPORTS: nothing
* ASSERTIONS:
******************************************************************************/
void freeNode(LinkedListNode *head)
{
   LinkedListNode* temp;

   while (head != NULL)
   {
      temp = head;
      head = head->next;
      fullFree(temp->data);
      fullFree(temp);
   }
}

/******************************************************************************
* NAME: fullFree
* PURPOSE: frees a pointer and points it to NULL
* IMPORTS: ptr, the pointer to be freed
* EXPORTS: nothing
* ASSERTIONS:
******************************************************************************/
void fullFree(void *ptr)
{
   free(ptr);
   ptr = NULL;
}
