#define _LASER_TANK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "movement.h"
#include "mirrors.h"
#include "linkedlist.h"
#include "newSleep.h"

int main(int argc, char* argv[])
{
	int **array = NULL;   /* initializing an array called 'array' */
	int r, c, pr, pc, er, ec;   /* initializing variables for array row, array column, player row, player column, enemy row and enemy column respectively */
	char *pd = NULL, *ed = NULL;   /* initializing character pointers to point to player direction and enemy direction */
	int ro, op, new, ind, temp;   /* initializing integer variables that will be assigned a specific value later in the program */
	int i, ii, iii;   /* initialising integer variables that would be used for looping later in the program */
	char opt;   /* initialising character variable that will be assigned a specific value later in the program */
	LinkedList *LL = NULL;   /* initializing a 'LinkedList' pointer called 'LL' */
	LinkedList *arrOut = NULL;   /* initializing a 'LinkedList' pointer called 'LL' */
	mirror *refl = NULL;   /* initializing a 'mirror' struct pointer called 'refl' */
	map *arr = NULL;   /* initializing a 'map' struct pointer called 'arr' */
	LinkedListNode *curr = NULL;   /* initializing a 'LinkedListNode' pointer called 'curr' */
	LinkedListNode *curr2 = NULL;   /* initializing a 'LinkedListNode' pointer called 'curr2' */
	FILE *inPtr;   /* initializing input file */
	FILE *outPtr;   /* initializing output file */
	
	if( argc != 3 )   /* if the number of arguments given in from the terminal is not 3 */
	{
		printf( "Not enough arguments.\n" );   /* print message to inform user */
		temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
	}
	else
	{
		inPtr = fopen( argv[1], "r" );   /* opening file given in argument 1 in read mode */
		outPtr = fopen( argv[2], "w" );   /* opening file given in argument 2 in write mode */
		LL = createLinkedList();   /* using the function in 'linkedlist.h' to create a linked list called 'LL' */
		arrOut = createLinkedList();   /* using the function in 'linkedlist.h' to create a linked list called 'arrOut' */
		
		if( inPtr == NULL || outPtr == NULL )   /* in the case the files could not be opened */
		{
			perror( "Could not open files.\n" );   /* print error message */
			temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
		}
		else
		{
			fscanf( inPtr, "%d %d", &r, &c );   /* read two integer values from first line of input file and assign the first to 'r' (number of rows for array) and the second to 'c' (number of columns of array) */
			
			while( ind != EOF )   /* while the end of file has not been reached */
			{
				refl = ( mirror * )malloc( sizeof( mirror ) );   /* allocating memory to create a struct pointed by 'refl' */
				ind = fscanf( inPtr, "%d %d %c", &refl->row, &refl->col, &refl->direc );   /* read a line from input file with 2 integers and character, assigning them to the 'row' value, 'col' value and 'direc' value in the refl struct respectively. 'ind' will have a value of 'EOF' if it is at the end of the input file */
				
				if(ind != EOF )   /* if ind is not at the end of the input file */
				{
					insertStart( LL, refl );   /* insert the struct into the linked list 'LL' */
				}
			}
			
			curr = LL->head;   /* point the 'curr' to where the head of the linked list 'LL' points to (i.e. at the first node) */
			
			while( curr->next != NULL )   /* while 'curr' does not point to the last node */
			{
				curr = curr->next;   /* point 'curr' to the next node */
			}
			
			pr = ((mirror *)curr->data)->row;   /* assign the 'row' of the last node to the player row */
			pc = ((mirror *)curr->data)->col;   /* assign the 'col' of the last node to the player column */
			pd = &( ((mirror *)curr->data)->direc );   /* assign the 'direc' of the last  node to the player direction */
			
			
			curr2 = LL->head;   /* point the 'curr2' to where the head of the linked list 'LL' points to (i.e. at the first node) */
			
			while( curr2->next->next != NULL )   /* while 'curr2' does not point to the second last node */
			{
				curr2 = curr2->next;   /* point 'curr2' to the next node */
			}
			
			er = ((mirror *)curr2->data)->row;   /* assign the 'row' of the last node to the enemy row */
			ec = ((mirror *)curr2->data)->col;   /* assign the 'col' of the last node to the enemy column */
			ed = &( ((mirror *)curr2->data)->direc );   /* assign the 'direc' of the last  node to the enemy direction */
			
			temp = 1;   /* assumes play map dimensions are correct and player and enemy are still alive (i.e. game is running) */
		}
	}
	
	while( temp == 1 )   /* condition to run the program as long as accurate row and column size are given and player and enemy are within them */
	{
		/* the following lines of code check whether the array dimensions are within the required range */
		if( r < 5 || r > 25 || c < 5 || c > 25 )
		{
			printf( "Play map dimensions must be between 5 and 25.\n" );   /* print error message */
			temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
		}
		
		/* the following lines of code check whether the player and enemy coordinates are within the row and column ranges */
		if( pr < 1 || pr > r || pc < 1 || pc > c )
		{
			printf( "Player coordinates out of play map.\n" );   /* print error message */
			temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
		}
		
		if( er < 1 || er > r || ec < 1 || ec > c )
		{
			printf( "Enemy coordinates out of play map.\n" );   /* print error message */
			temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
		}
		
		while( temp == 1 )   /* provided that all the previous conditions have been met */
		{
			array = ( int** ) malloc( r * sizeof( int * ) );   /* heap memory allocated; the size of the rows of the array */
			for( ro = 0 ; ro <= r; ro++ )
			{
				array[ro] = ( int* ) malloc( c * sizeof( int ) );   /* heap memory allocated; size of the columns of the array - array has been set up */
			}
			
			for( i = 0; i <= r; i++ )   /* the value of 'i' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
			{
				for( ii = 0; ii <= c; ii++ )   /* the value of 'ii' starts from 0 and increments as long as it stays less than or equal to the amount of array columns */
				{
					array[i][ii] = ' ';   /* set the value of array coordinate to be empty */
				}
			}
			
			/* The following lines of code add the '*' symbol to the array boundaries */
			for( i = 0; i <= c; i++ )
			{
				array[0][i] = '*';
				array[r][i] = '*';
			}
			for( ii = 0; ii <= r; ii++ )
			{
				array[ii][0] = '*';
				array[ii][c] = '*';
			}
		
			/* the following lines of code adds the player into the play map using the player coordinates provided */
			if( strcmp( pd, "u" ) == 0 )   /* compares the player direction input given in command line argument with the letter 'u' and if true, player direction is upwards */
			{
				array[pr][pc] = '^';
			}
			else if( strcmp( pd, "d" ) == 0 )   /* compares player direction with 'd' and if true, player direcion is downwards */
			{
				array[pr][pc] = 'v';
			}
			else if( strcmp( pd, "l" ) == 0 )   /* compares player direction with 'l' and if true, player direcion is left-aligned */
			{
				array[pr][pc] = '<';
			}
			else if( strcmp( pd, "r" ) == 0 )   /* compares player direction with 'r' and if true, player direcion is right-aligned */
			{
				array[pr][pc] = '>';
			}	
			else   /* in the case no accurate direction is given, the default: right-aligned direction is chosen */
			{
				array[pr][pc] = '>';
			}
			
			/* the following lines of code apply to printing the enemy in the enemy coordinates with the same process as explained for printing the player */
			if( strcmp( ed, "u" ) == 0 )
			{
				array[er][ec] = '^';
			}
			else if( strcmp( ed, "d" ) == 0 )
			{
				array[er][ec] = 'v';
			}
			else if( strcmp( ed, "l" ) == 0 )
			{
				array[er][ec] = '<';
			}
			else if( strcmp( ed, "r" ) == 0 )
			{
				array[er][ec] = '>';
			}	
			else
			{
				array[er][ec] = '>';
			}
			
			temp = putMirror( array, r, c, LL );   /* runs the 'putMirror()' function in the 'mirror.c' file to add the mirrors from the linked list 'LL' onto the array map, assigning a value of 1 if all the maps have been successfully added into the array map */
			
			if( temp == 0 )   /* in the case the a mirror was not added into the array map */
			{
				for( iii = 0; iii < r; iii++ )   /* the value of 'iii' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
				{
					free( array[iii] );   /* free's the heap memory located using malloc for the array rows */
				}
				free( array );   /* free's the heap memory located using malloc for the array */
				/*freeLinkedList2( LL, &freeData2 );
				freeLinkedList( arrOut, &freeData, r);*/
				
				free( curr );   /* free's 'curr' variable */
				free( curr2 );   /* free's 'curr2' variable */
				free( refl );   /* free's 'refl' variable */
				free( arr );   /* free's 'arr' variable */
				
				fclose( inPtr );   /* closes the input file */
				fclose( outPtr );   /* closes the output file */
			}
			
			while( temp != 0 )   /* provided that all the previous conditions have been met */
			{
				while( ( opt != 'f' && opt != 'l' ) && op != 'b' && temp == 1 )   /* run the next lines of code as long as the option selected is not 'f' or 'l' and the value of op is not 'b' and temp has a value of 1 */
				{	
					system( "clear" );   /* clears the terminal window */
					new = move( array, r, c, &pr, &pc, er, ec, opt, pd, ed, outPtr, arr, arrOut );   /* moves the player in the map with respect to the type of option selected and returns a value 'a' if the player has been killed into 'new' */
					
					if( new == 'a' )   /* if player has been killed proceed with next lines of code */
					{
						op = 'b';   /* gives 'op' a value of 'b' whereby the code (line 204) would break */
						temp = 0;   /* gives 'temp' a value of 0 whereby the code (line 204 and line 202) would break and the program would not carry on anymore */
					}
					
					if( op != 'b' )   /* as long as the program is running (i.e. the player is still alive)... */
					{
						opt = menu();   /* ...print the option menu and pass the selected option into 'opt' */
						copyArray( array, r, c, arr, arrOut );   /* runs the 'copyArray()' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
					}
					
					outPtr = fopen( argv[2], "w" );   /* re-opens the output file in writing mode */
					if( outPtr == NULL )   /* in the case the file could not be opened */
					{
						perror( "Could not open output file.\n" );   /* print error message */
						temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
					}
				}
				
				if( opt == 'l' )   /* if the selected option is 'l'... */
				{
					output( r, c, outPtr, arrOut );   /* runs the 'output' function in the 'mirrors.c' that will empty the linked list 'arrOut' and print each node into the output file */
					fclose( outPtr );   /* closes the output file */
					printf( "Saved !\n" );   /* informs user that file has been saved */
					newSleep( 1.5 );   /* makes the terminal sleep for 1.5 seconds using the 'newSleep()' function in 'newSleep.c' */
					/*freeLinkedList( arrOut, &freeData, r);*/
					arrOut = createLinkedList();   /* clear the linked list and creates an empty new one */
					opt = '0';   /* assign 'opt' a value of 0 to prevent continuous looping from occuring within the player map and restart from line 204 */
				}		
				else if( opt == 'f' )   /* if the selected option is 'f'... */
				{
					temp = shoot( array, r, c, pr, pc, *pd, er, ec, outPtr, arr, arrOut );   /* ...initialize the shoot function in 'functions.c' and pass the output to 'temp' */
					if( temp == 1 )   /* as long as the enemy is not dead, the game continues */
					{
						opt = '0';   /* assign 'opt' a value of 0 to prevent continuous looping from occuring within the player map and restart from line 204 */
					}
					else if( temp == 0 )   /* as long as the enemy is dead, the game ends */
					{	
						for( iii = 0; iii < r; iii++ )   /* the value of 'iii' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
						{
							free( array[iii] );   /* free's the heap memory located using malloc for the array  rows */
						}
						free( array );   /* free's the heap memory located using malloc for the array */
						/*freeLinkedList2( LL, &freeData2 );
						freeLinkedList( arrOut, &freeData, r);*/
						
						free( curr );   /* free's 'curr' variable */
						free( curr2 );   /* free's 'curr2' variable */
						free( refl );   /* free's 'refl' variable */
						free( arr );   /* free's 'arr' variable */
						
						fclose( inPtr );   /* closes the input file */
						fclose( outPtr );   /* closes the output file */
					}
				}
				else if( opt != ( 'w' || 's' || 'a' || 'd' || 'f' || 'l' ) )   /* if the selected option is not 'w', 's', 'a', 'd', 'f' or 'l'... */
				{
					opt = '0';   /* ignore the option and restart from line 204 */
				}
			}
		}
	}

	return 0;
}
