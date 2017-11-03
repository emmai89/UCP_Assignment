/****************************************************************************
 * FILE: LinkedList.h
 * AUTHOR: Emmanuel Iloh
 * Student Number: 18817599
 * UNIT: UNIX and C Programming (COMP1000)
 * PURPOSE: foward declarations of the LinkedList.c functions and structs
 * REFERENCE: none
 * LAST MOD: 2017-10-27
 * COMMENTS:
 *****************************************************************************/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKLIST
#define LINKLIST

typedef struct LinkedListNode
{
   struct LinkedListNode* next;
   void* data;
} LinkedListNode;

typedef struct
{
   LinkedListNode* head, *tail;
   int length;
} LinkedList;

LinkedList* emptyList();
void insertFirst(LinkedList *list, void* data);
void insertLast(LinkedList *list, void* entry);
void* removeFirst(LinkedList *list);
void* find(int num, LinkedList *list);
LinkedListNode* findRec(int num, LinkedListNode* node);
void display(LinkedList* list);
void freeLinkedList(LinkedList* list);
void freeNode(LinkedListNode *head);
void fullFree(void *ptr);

#endif
