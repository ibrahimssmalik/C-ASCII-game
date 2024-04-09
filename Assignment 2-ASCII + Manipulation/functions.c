#define _FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "movement.h"
#include "mirrors.h"
#include "linkedlist.h"
#include "newSleep.h"

/* the following function prints out an array (returning nothing) */
void prtArr( int **Arr, int row, int col )
{
	int i, ii;   /* initializing integer variables that would be used for looping later in the function */
	
	for( i = 0; i <= row; i++ )   /* the value of 'i' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
	{
		for( ii = 0; ii <= col; ii++ )   /* the value of 'ii' starts from 0 and increments as long as it stays less than or equal to the amount of array columns */
		{
			printf( "%c", Arr[i][ii] );   /* print the character that is in row 'i' and column 'ii' of the array */
		}
		printf( "\n" );   /* prints whatever is to be printed next on the next line */
	}
}

/* the following function prints out the option menu (returning a character) */
char menu( void )
{	
	char action;   /* initializing character variable that would be used to output data later in the function */
	
	/* the following lines of code print the available options from which the user can select */
	printf( "w to go/face up\n" );
	printf( "s to go/face down\n" );
	printf( "a to go/face left\n" );
	printf( "d to go/face right\n" );
	printf( "f to shoot laser\n" );
	printf( "l to save the Log\naction: " );
	
	scanf( "%s", &action );   /* allows the user to input an option of choice from the menu and assign it to 'action' */
	
	return action;   /* the option selected by the user is the output of the function */
}

/* the following function prints out an array (returning nothing) */
void redPrint( int **array, int row, int col, int sr, int sc )
{	
	int i, ii;   /* re-occuring from the 'prtArr()' function */

	for( i = 0; i <= row; i++ )   /* re-occuring from the 'prtArr()' function */
	{
		for( ii = 0; ii <= col; ii++ )   /* re-occuring from the 'prtArr()' function */
		{
			if( i != sr || ii != sc )   /* if the coordinates under consideration are not the coordinates of the symbol '-' or '|' */
			{
				printf( "%c", array[i][ii] );   /* re-occuring from the 'prtArr()' function */
			}
			else
			{
				printf( "\033[0;31m" );   /* change font color into red color for the oncoming printf function */
				
				printf( "%c", array[i][ii] );   /* re-occuring from the 'prtArr()' function */
				
				printf( "\033[0m" );   /* change font color back to default color - basically a reset button)*/
			}
		}
		printf( "\n" );   /* re-occuring from the 'prtArr()' function */
	}
}

/* the following function shows laser being hit by the player (returning an integer) */
int shoot( int **array, int arow, int acol, int pr, int pc, char pd, int er, int ec, void *outPtr, map *arr, LinkedList *arrOut )
{
	int sym1, sym2;   /* initializing integer variable that would be used to define type of symbol later in the function */
	int test, playr, playc;   /* initializing integer variables that will be assigned a specific value later in the program */
	int outp, output;   /* initializing integer variables that would be used to output data later in the function */
	
	sym1 = '-';   /* defining symbol 1 to be '-' */
	sym2 = '|';   /* defining symbol 1 to be '|' */
	test = 0;   /* pre-set value of test set to 0 */
	outp = 1;   /* pre-set value of outp set to 0 */
	output = 1;   /* pre-set value of output set to 1 */
	playr = pr;   /* playr stores the value of the player row */
	playc = pc;   /* playc stores the value of the player column */
	
	system( "clear" );   /* clears the terminal window */
	
	while( ( outp == 1 ) && ( output == 1 ) )   /* while the value of outp and output remains 1 */
	{
		if( pd == 'r' )   /* in the case the players direction is right-aligned */
		{
			while( ( pc < ( acol - 1 ) ) && ( pd == 'r' ) )   /* keep incrementing the player column value until it reaches the second-last value (ie. just before play map boundary) and while the player direction remains right-aligned */
			{
				test = changeShoot( array, arow, acol, pd, pr, pc );   /* run the 'changeShoot()' function in 'mirrors.c' which will return a value of 1 incase there is a mirror next to the player */
				if( test == 0 )   /* in case there is no mirror next to the player */
				{
					pc = pc + 1;   /* pc holds the column of the laser which is in the next column of the player */
					array[pr][pc] = sym1;   /* adds symbol 1 into the column next to the player column */
				}
				
				if( array[er][ec] == sym1 )   /* if the symbol or 'laser' hits the enemy */
				{
					array[er][ec-1] = ' ';   /* erases the laser before the enemy column to make it disappear in play map */
					win( array, arow, acol, er, ec, outPtr, arr, arrOut );   /* initializes the 'win()' function to win the game */
					output = 0;   /* new 'output' value is '0' which will be returned by the function and will break from the loop in line 87 */
					pc = acol - 1;   /* this is done to break from the loop in line 91 so no more increments can take place and the game has ended */
				}
				else if ( array[playr][playc] == sym1 )   /* if the symbol or 'laser' hits the player */
				{
					array[playr][playc-1] = ' ';   /* erases the laser before the player column to make it disappear in play map */
					loose( array, arow, acol, playr, playc, outPtr, arr, arrOut );   /* initializes the 'loose()' function to loose the game */
					output = 0;   /* new 'output' value is '0' which will be returned by the function and will break from the loop in line 87 */
					pc = acol - 1;   /* this is done to break from the loop in line 91 so no more increments can take place and the game has ended */
				}
				else   /* in case the player and enemy are still alive in play map */
				{
					if( test == 0 )   /* in case there is no mirror next to the player */
					{
						if( pc == ( acol - 1 ) )   /* if the laser is hit just before the map boundary */
						{
							outp = 0;   /* new 'output' value is '0' and will break from the loop in line 87 */
						}
						redPrint( array, arow, acol, pr, pc );   /* prints the play map with the laser in red color using the 'redPrint()' function */
						copyArray( array, arow, acol, arr, arrOut );   /* runs the 'copyArray' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
						test = changeShoot( array, arow, acol, pd, pr, pc );   /* run the 'changeShoot()' function in 'mirrors.c' which will return a value of 1 incase there is a mirror next to the laser */
						array[pr][pc] = ' ';   /* erases the laser before printing it in next column to make it disappear in play map */
						newSleep( 0.5 );   /* makes the terminal sleep for 0.5 seconds using the 'newSleep()' function in 'newSleep.c' */
						system( "clear" );   /* clears the terminal window */
					}
					else if( test == 1 )   /* in case there is a backward mirror next to the laser */
					{
						redPrint( array, arow, acol, pr+1, pc );   /* prints the play map with the laser in red color using the 'redPrint()' function */
						copyArray( array, arow, acol, arr, arrOut );   /* runs the 'copyArray' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
						pd = 'd';   /* change the player direction to downwards and hence breaking the loop in line 91 */
						pc = pc + 1;   /* pc holds the column of the laser which is in the next column of the previous laser */
						newSleep( 0.5 );   /* makes the terminal sleep for 0.5 seconds using the 'newSleep()' function in 'newSleep.c' */
						system( "clear" );   /* clears the terminal window */
					}
					else if( test == 2 )   /* in case there is a forward mirror next to the laser */
					{
						redPrint( array, arow, acol, pr-1, pc );   /* prints the play map with the laser in red color using the 'redPrint()' function */
						copyArray( array, arow, acol, arr, arrOut );   /* runs the 'copyArray' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
						pd = 'u';   /* change the player direction to upwards and hence breaking the loop in line 91 */
						pc = pc + 1;   /* pc holds the column of the laser which is in the next column of the previous laser */
						newSleep( 0.5 );   /* makes the terminal sleep for 0.5 seconds using the 'newSleep()' function in 'newSleep.c' */
						system( "clear" );   /* clears the terminal window */
					}
				}
			}
		}
		
		else if( pd == 'l' )   /* in the case the players direction is left-aligned */
		{		
		/* the following lines of code perform the same function as lines 89-149 explained above with only decrements taking place instead of increments */
			while( ( pc > 1 ) && ( pd == 'l' ) )
			{
				test = changeShoot( array, arow, acol, pd, pr, pc ); /* checks for mirrors next to player */			
				if( test == 0 )   /* if no mirror found */
				{
					pc = pc - 1;   /* laser column (just before player column) */
					array[pr][pc] = sym1;   /* adding laser on map */
				}
				
				if( array[er][ec] == sym1 )   /* if laser hits enemy */
				{
					array[er][ec+1] = ' ';   /* erasing the laser from the map */
					win( array, arow, acol, er, ec, outPtr, arr, arrOut );   /* initializing the 'win()' function */
					output = 0;   /* specific value for 'output' meaning the game has ended */
					pc = 1;   /* ends the decrement loop */
				}
				else if ( array[playr][playc] == sym1 )   /* if laser hits player */
				{
					array[playr][playc+1] = ' ';   /* erasing the laser from the map */
					loose( array, arow, acol, playr, playc, outPtr, arr, arrOut );   /* initializes the 'loose()' function */
					output = 0;   /* specific value for 'output' meaning the game has ended */
					pc = 1;   /* ends the decrement loop */
				}
				else   /* player and enemy still alive */
				{
					if( test == 0 )   /* if no mirror next to player */
					{
						if( pc == ( 1 ) )   /* if laser is just before map boundary */
						{
							outp = 0;   /* ends loop in line 87 */
						}
						redPrint( array, arow, acol, pr, pc );   /* prints array */
						copyArray( array, arow, acol, arr, arrOut );   /* copies current condition of array map into linked list */
						test = changeShoot( array, arow, acol, pd, pr, pc );   /* checks for mirrors next to laser */
						array[pr][pc] = ' ';   /* erases current laser */
						
						newSleep( 0.5 );   /* makes terminal sleep */
						system( "clear" );   /* clears terminal window */
					}
					else if( test == 1 )   /* if backward mirror next to laser */
					{
						redPrint( array, arow, acol, pr-1, pc );   /* prints array */
						copyArray( array, arow, acol, arr, arrOut );   /* copies current condition of array map into linked list */
						pd = 'u';   /* changes player direction to upwards direction */
						pc = pc - 1;   /* hold the next position of laser */
						newSleep( 0.5 );   /* makes terminal sleep */
						system( "clear" );   /* clears terminal window */
					}
					else if( test == 2 )   /* if forward mirror next to laser */
					{
						redPrint( array, arow, acol, pr+1, pc );   /* prints array */
						copyArray( array, arow, acol, arr, arrOut );   /* copies current condition of array map into linked list */
						pd = 'd';   /* changes player direction to downwards direction */
						pc = pc - 1;   /* hold the next position of laser */
						newSleep( 0.5 );   /* makes terminal sleep */
						system( "clear" );   /* clears terminal window */
					}
				}
			}
		}
		
		else if( pd == 'u' )   /* in the case the players direction is upwards */
		{	
		/* the following lines of code perform the same function as lines 89-149 explained above with only decrements taking place instead of increments */
			while( ( pr > 1 ) && ( pd == 'u' ) )
			{
				test = changeShoot( array, arow, acol, pd, pr, pc );
				
				if( test == 0 )
				{
					pr = pr - 1;
					array[pr][pc] = sym2;   /* symbol 2 is used in this case since the laser is travelling upwards */
				}
				
				if( array[er][ec] == sym2 )
				{
					array[er+1][ec] = ' ';
					win( array, arow, acol, er, ec, outPtr, arr, arrOut );
					output = 0;
					pr = 1;
				}
				else if ( array[playr][playc] == sym2 )
				{
					array[playr+1][playc] = ' ';
					loose( array, arow, acol, playr, playc, outPtr, arr, arrOut );
					output = 0;
					pr = 1;
				}
				else
				{
					if( test == 0 )
					{
						if( pr == ( 1 ) )
						{
							outp = 0;
						}
						redPrint( array, arow, acol, pr, pc );
						copyArray( array, arow, acol, arr, arrOut );
						test = changeShoot( array, arow, acol, pd, pr, pc );
						array[pr][pc] = ' ';

						newSleep( 0.5 );
						system( "clear" );
					}
					
					else if( test == 1 )
					{
						redPrint( array, arow, acol, pr, pc-1 );
						copyArray( array, arow, acol, arr, arrOut );
						pd = 'l';
						pr = pr - 1;
						newSleep( 0.5 );
						system( "clear" );
					}
					else if( test == 2 )
					{
						redPrint( array, arow, acol, pr, pc+1 );
						copyArray( array, arow, acol, arr, arrOut );
						pd = 'r';
						pr = pr - 1;
						newSleep( 0.5 );
						system( "clear" );
					}
				}
			}
		}
		
		else if( pd == 'd' )   /* in the case the players direction is downwards */
		{	
		/* the following lines of code perform the same function as lines 79-99 explained above with only increments taking place */	
			while( ( pr < arow - 1 ) && ( pd == 'd' ) )
			{
				test = changeShoot( array, arow, acol, pd, pr, pc );
				
				if( test == 0 )
				{
					pr = pr + 1;
					array[pr][pc] = sym2;
				}
				
				if( array[er][ec] == sym2 )
				{
					array[er-1][ec] = ' ';
					win( array, arow, acol, er, ec, outPtr, arr, arrOut );
					output = 0;
					pr = arow - 1;
				}
				else if ( array[playr][playc] == sym2 )
				{
					array[playr-1][playc] = ' ';
					loose( array, arow, acol, playr, playc, outPtr, arr, arrOut );
					output = 0;
					pr = arow - 1;
				}
				else
				{
					if( test == 0 )
					{
						if( pr == ( arow - 1 ) )
						{
							outp = 0;
						}
						redPrint( array, arow, acol, pr, pc );
						copyArray( array, arow, acol, arr, arrOut );
						test = changeShoot( array, arow, acol, pd, pr, pc );
						array[pr][pc] = ' ';

						newSleep( 0.5 );
						system( "clear" );
					}
					else if( test == 1 )
					{
						redPrint( array, arow, acol, pr, pc+1 );
						copyArray( array, arow, acol, arr, arrOut );
						pd = 'r';
						pr = pr + 1;
						newSleep( 0.5 );
						system( "clear" );
					}
					else if( test == 2 )
					{
						redPrint( array, arow, acol, pr, pc-1 );
						copyArray( array, arow, acol, arr, arrOut );
						pd = 'l';
						pr = pr + 1;
						newSleep( 0.5 );
						system( "clear" );
					}
				}
			}
		}
	}
	
	return output;   /* 'output' is the variable that is returned by this function; having a value of 0 if the game has ended and having a value of 1 if the game is still running */
}

/* the following function declares that the user has won the game (returning nothing) */
void win( int **array, int row, int col, int er, int ec, void *outPtr, map *arr, LinkedList *arrOut )
{
	array[er][ec] = 'X';   /* the enemy tank is now replaced with 'X' indicating that it has died */
	prtArr( array, row, col );   /* prints the array using the function 'prtArr()' */
	copyArray( array, row, col, arr, arrOut );   /* runs the 'copyArray' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
	output( row, col, outPtr, arrOut );   /* runs the 'output' function in the 'mirrors.c' that will empty the linked list 'arrOut' and print each node into the output file */
	printf( "You Win !!!\n" );   /* prints statement informing user that they have won the game */
}

/* the following function declares that the user has lost the game (returning nothing) */
void loose( int **array, int row, int col, int pr, int pc, void *outPtr, map *arr, LinkedList *arrOut )
{
	array[pr][pc] = 'X';   /* the player tank is now replaced with 'X' indicating that it has died */
	prtArr( array, row, col );   /* prints the array using the function 'prtArr()' */
	copyArray( array, row, col, arr, arrOut );   /* runs the 'copyArray' function in 'mirrors.c' to add the current state of the array into the linked list 'arrOut' */
	output( row, col, outPtr, arrOut );   /* runs the 'output' function in the 'mirrors.c' that will empty the linked list 'arrOut' and print each node into the output file */
	printf( "You Lose !!!\n" );   /* prints statement informing user that they have won the game */
}
