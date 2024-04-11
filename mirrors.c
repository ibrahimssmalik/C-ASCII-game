#define _MIRRORS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mirrors.h"
#include "functions.h"
#include "movement.h"
#include "linkedlist.h"
#include "newSleep.h"

/* the following function puts mirrors in the play map using a linked list (returning an integer) */
int putMirror( int **Arr, int row, int col, LinkedList *LL )
{
	int Mrow;   /* initializing a variable to hold the row coordinate of a mirror */
	int Mcol;   /* initializing a variable to hold the column coordinate of a mirror */
	char *Mdirec;   /* initializing a variable to hold the direction of a mirror */
	int temp;   /* initializing integer variable that would be used to output data later in the function */
	int coun;   /* initializing integer variables that will be assigned a specific value later in the program */
	
	LinkedListNode *curr = NULL;   /* initializing a 'LinkedListNode' pointer called 'curr' */
	temp = 1;   /* pre-set value of output set to 1 */
	coun = ( LL->count ) - 1;   /* pre-set value of coun is the number of mirrors - 1 */
	curr = LL->head;   /* point the 'curr' to where the head of the linked list 'LL' points to (i.e. at the first node) */
	
	while( curr->next->next !=  NULL )   /* while 'curr' does not point to the second last node */
	{
		coun = coun - 1;   /* mirror number */
		Mrow = ( ( mirror * ) curr->data )->row;   /* assign the 'row' of the mirror to the mirror row variable */
		Mcol = ( ( mirror * ) curr->data )->col;   /* assign the 'col' of the mirror to the mirror column variable */
		Mdirec = &( ( mirror * ) curr->data )->direc;   /* assign the 'direc' of the mirror to the mirror direction variable */
		
		if( ( Mrow > 0 ) && ( Mrow < row ) && ( Mcol > 0 ) && ( Mcol < col ) )   /* if the mirror row and mirror column values are within the array map parameters */
		{
			if( strcmp( Mdirec, "b" ) == 0 )   /* compares the mirrors direction with the letter 'b' */
			{
				Arr[Mrow][Mcol] = '\\';   /* place a backward slash as the mirror in the row and column coordinate of the mirror in the play map */
			}
			else if( strcmp( Mdirec, "f" ) == 0 )   /* compares the mirrors direction with the letter 'f' */
			{
				Arr[Mrow][Mcol] = '/';      /* place a forward slash as the mirror in the row and column coordinate of the mirror in the play map */
			}
		}
		else   /* if the mirror row and mirror column values are NOT within the array map parameters */
		{
			printf( "Mirror #%d: (%d %d %s) not added.\n", coun, Mrow, Mcol, Mdirec );   /* print an error message informing player of inaccurate mirrors not added in map */
			temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
		}
		
		curr = curr->next;   /* point 'curr' to the next node */
	}
	
	free( curr );   /* free 'curr' variable */
	
	return temp;   /* 'temp' is the variable that is returned by this function; having a value of 0 if the game will not start and having a value of 1 if the game will be starting */
}

/* the following function checks whether there is a mirror next to a specific array coordinate (returning an integer) */
int changeShoot( int **Arr, int row, int col, char pd, int Lrow, int Lcol )
{
	int test;   /* initializing integer variable that would be used to output data later in the function */
	test = 0;   /* pre-set value of output set to 0 */
	
	if( pd == 'r' )   /* when the player is facing right-aligned */
	{
		if( Arr[Lrow][Lcol+1] == '\\' )   /* if there is backward slash next to the player */
		{
			test = 1;   /* change value of test to 1 */
		}
		else if( Arr[Lrow][Lcol+1] == '/' )   /* if there is forward slash next to the player */
		{
			test = 2;   /* change value of test to 2 */
		}
	}
	/* the following lines of code perform the same function as lines 63-73 explained above with only difference in the player direction */
	else if( pd == 'l' )
	{
		if( Arr[Lrow][Lcol-1] == '\\' )
		{
			test = 1;
		}
		else if( Arr[Lrow][Lcol-1] == '/' )
		{
			test = 2;
		}
	}
	else if( pd == 'u' )
	{
		if( Arr[Lrow-1][Lcol] == '\\' )
		{
			test = 1;
		}
		else if( Arr[Lrow-1][Lcol] == '/' )
		{
			test = 2;
		}
	}
	else if( pd == 'd' )
	{
		if( Arr[Lrow+1][Lcol] == '\\' )
		{
			test = 1;
		}
		else if( Arr[Lrow+1][Lcol] == '/' )
		{
			test = 2;
		}
	}
	
	return test;   /* 'test' is the variable that is returned by this function; having a value of 0 if there is no mirror in front of the player and having a value of 1 or 2 if there is a backward or forward slash respectively */
}

/* the following function copies the array map to the struct variable and inserts into a linked list (returning nothing) */
void copyArray( int **Arr, int row, int col, map *arr, LinkedList *LL )
{	
	int i, j;   /* initializing integer variables that would be used for looping later in the function */
	
	arr = ( map * )malloc( sizeof( map ) );   /* allocating memory to create a struct pointed by 'arr' */
	
	( arr->copy ) = ( int** ) malloc( row * sizeof( int * ) );   /* heap memory allocated; the size of the rows of the array */
	for( j = 0; j <= col; j++ )
	{
		( arr->copy )[j] = ( int* ) malloc( col * sizeof( int ) );   /* heap memory allocated; size of the columns of the array - array in node has been set up */
	}
	
	for( i = 0; i <= row; i++)   /* the value of 'i' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
	{
		for( j = 0; j <= col; j++ )   /* the value of 'j' starts from 0 and increments as long as it stays less than or equal to the amount of array columns */
		{
			arr->copy[i][j] = Arr[i][j];   /* copy value in array to the copy array in the node - resulting in the same copy of the array */
		}
	}
	
	insertLast( LL, arr );   /* inserts the arr node at the start of the linked list 'LL' */
}

/* the following function prints each node in a linked list into a file (returning nothing) */
void output( int row, int col, void *outPtr, LinkedList *LL )
{
	int i, j;   /* initializing integer variables that would be used for looping later in the function */
	char info;   /* initializing character variable that would be used later in the function */
	
	LinkedListNode *curr = NULL;   /* initializing a 'LinkedListNode' pointer called 'curr' */
	curr = LL->head;   /* point the 'curr' to where the head of the linked list 'LL' points to (i.e. at the first node) */
	
	while( curr != NULL)   /* while 'curr' does not point to the last node */
	{
		for( i = 0; i <= row; i++ )   /* the value of 'i' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
		{
			for( j = 0; j <= col; j++ )   /* the value of 'j' starts from 0 and increments as long as it stays less than or equal to the amount of array columns */
			{
				info = ( ( map * ) curr->data )->copy[i][j];   /* assign the coordinate of the copy map to the info variable */
				fprintf( outPtr, "%c", info );   /* print the character of the info variable to the file 'outPtr' */
			}
			fprintf( outPtr,"\n" );   /* prints whatever is to be printed next on the next line in the file 'outPtr' */
		}
		
		fprintf( outPtr, "\n\n--------------------------------------------------\n\n\n" );   /* prints a dashed line in the 'outPtr' file to make it easier to distinguish between the previous and current array map */		
		curr = curr->next;   /* point 'curr' to the next node */
	}
	
	free( curr );	
}
