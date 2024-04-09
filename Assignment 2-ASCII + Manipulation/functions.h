#include "linkedlist.h"
#ifndef HEADER_FUNCTIONS
#define HEADER_FUNCTIONS

void prtArr( int **Arr, int row, int col );

char menu( void );

void redPrint( int **array, int row, int col, int sr, int sc );

int shoot( int **array, int arow, int acol, int pr, int pc, char pd, int er, int ec, void *outPtr, map *arr, LinkedList *arrOut );

void win( int **array, int row, int col, int er, int ec, void *outPtr, map *arr, LinkedList *arrOut );

void loose( int **array, int row, int col, int pr, int pc, void *outPtr, map *arr, LinkedList *arrOut );

#endif
