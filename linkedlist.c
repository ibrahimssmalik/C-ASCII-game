/* THIS FILE HAS BEEN TAKEN FROM UCP - PRACTICAL 06 AS PERMITTED THROUGH ASSIGNMENT SPECIFICATIONS */


#define _LINKED_LIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "functions.h"
#include "movement.h"
#include "mirrors.h"
#include "newSleep.h"

/* the following function prints out data from a struct (returning nothing) */
void printResult(void *data)
{
	printf("%d %d %c\n", ((mirror *)data)->row, ((mirror *)data)->col, ((mirror *)data)->direc);
}

/* the following function free's a struct variable (returning nothing) */
void freeData(void *data, int row)
{
	int i;
	
	for(i = 0; i < row; i++)
	{
		free((((map *)data)->copy)[i]);
	}
	free(((map *)data)->copy);	
}

/* the following function free's a struct variable (returning nothing) */
void freeData2(void *data)
{
	free(((mirror *)data));	
}

/* the following function created a linked list with a head and count (returning the same linked list) */
LinkedList *createLinkedList(void)
{
	LinkedList *LL = NULL;
	LL = (LinkedList *)malloc(sizeof(LinkedList));
	LL->head = NULL;
	LL->count = 0;
	
	return LL;
}

/* the following function adds a node at the start of the linked list, before all other nodes (returning nothing) */
void insertStart(LinkedList* list, void* entry)
{
	LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	newNode->data = entry;
	newNode->next = list->head;
	list->head = newNode;
	list->count++;
}

/* the following function removes the node at the very start of the linked list (returning nothing) */
void *removeStart(LinkedList *list)
{
	void *data = NULL;
	LinkedListNode *firstNode = list->head;
	
	if(firstNode != NULL)
	{
		data = firstNode->data;
		list->head = firstNode->next;
		free(firstNode);
		list->count--;
	}
	
	return data;
}

/* the following function adds a node at the end of the linked list, after all other nodes (returning nothing) */
void insertLast(LinkedList* list, void* entry)
{
	LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	LinkedListNode *curr = list->head;
	newNode->next = NULL;
	newNode->data = entry;
	
	if(list->head == NULL)
	{
		list->head = newNode;
	}
	else
	{
		while(curr->next != NULL)
		{
			curr = curr->next;
		}
		
		curr->next = newNode;
	}
	list->count++;
}

/* the following function removes the node at the very end of the linked list (returning nothing) */
void *removeLast(LinkedList *list)
{
	void *data = NULL;
	LinkedListNode *curr = list->head;
	LinkedListNode *curr2 = list->head;
	
	if(list->head != NULL)
	{
		if(curr->next != NULL)
		{	
			while(curr->next != NULL)
			{
				curr = curr->next;
			}
			
			while(curr2->next->next != NULL)
			{
				curr2 = curr2->next;
			}
			data = curr->data;
			curr2->next = NULL;
		}
		else
		{
			data = curr->data;
			list->head = NULL;
		}
		
		free(curr);
		list->count--;
	}
	
	return data;
}

/* the following function prints the linked list by printing each node (returning nothing) */
void printLinkedList(LinkedList *list, listFunc funcPtr, int row)
{
	LinkedListNode *curr = list->head;
	while(curr != NULL)
	{
		(*funcPtr)(curr->data,row);
		curr = curr->next;
	}
	free(curr);
}

/* the following function free's the linked list by freeing each node (returning nothing) */
void freeLinkedList(LinkedList *list, listFunc funcPtr, int row)
{
	LinkedListNode *curr = list->head;
	LinkedListNode *nextCurr = NULL;
	
	while(curr != NULL)
	{
		nextCurr = curr->next;
		(*funcPtr)(curr->data,row);   /*free the data pointer*/
		free(curr);
		curr = nextCurr;
	}
	free(list);
}

/* the following function free's the linked list by freeing each node (returning nothing) */
void freeLinkedList2(LinkedList *list, listFun funcPtr)
{
	LinkedListNode *curr = list->head;
	LinkedListNode *nextCurr = NULL;
	
	while(curr != NULL)
	{
		nextCurr = curr->next;
		(*funcPtr)(curr->data);   /*free the data pointer*/
		free(curr);
		curr = nextCurr;
	}
	free(list);
}
