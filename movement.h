#include "linkedlist.h"
#ifndef HEADER_MOVE
#define HEADER_MOVE

int move( int **array, int row, int col, int *playr, int *playc, int er, int ec, char option, char *playDire, char *enemDire, void *outPtr, map *arr, LinkedList *arrOut );

int lose( int **array, int row, int col, int pr, int pc, int er, int ec, char ed, void *outPtr, map *arr, LinkedList *arrOut );

int kill( int **array, int row, int col, int pr, int pc, char pd, int er, int ec, void *outPtr, map *arr, LinkedList *arrOut );

#endif
