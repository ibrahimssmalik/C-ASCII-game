/* THIS FILE HAS BEEN TAKEN FROM UCP - PRACTICAL 06 AS PERMITTED THROUGH ASSIGNMENT SPECIFICATIONS */


#ifndef LL_HGUARD
#define LL_HGUARD

typedef struct{
	int row;
	int col;
	char direc;
} mirror;

typedef struct{
	int **copy;
} map;

void printResult(void *data);

void freeData(void *data, int row);
void freeData2(void *data);

typedef struct LinkedListNode{
	void *data;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct{
	LinkedListNode *head;
	int count;
} LinkedList;

typedef void (*listFunc)(void *data, int row);
typedef void(*listFun)(void *data);

LinkedList *createLinkedList(void);
void insertStart(LinkedList *list, void *entry);
void *removeStart(LinkedList *list);
void insertLast(LinkedList *list, void *entry);
void *removeLast(LinkedList *list);

void printLinkedList(LinkedList *list, listFunc funcPtr,int row);
void freeLinkedList(LinkedList *list, listFunc funcPtr, int row);
void freeLinkedList2(LinkedList *list, listFun funcPtr);

#endif
