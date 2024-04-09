#include "linkedlist.h"
#ifndef HEADER_MIRRORS
#define HEADER_MIRRORS

int putMirror( int **Arr, int row, int col, LinkedList *LL );

int changeShoot( int **Arr, int row, int col, char pd, int Lrow, int Lcol );

void copyArray( int **Arr, int row, int col, map *arr, LinkedList *LL );

void output( int row, int col, void *outPtr, LinkedList *LL );

#endif
