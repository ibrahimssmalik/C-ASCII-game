#define _FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "movement.h"
#include "newSleep.h"

/* the following function prints out an array (returning nothing) */
void prtArr( int **Arr, int row, int col )
{
	int i, ii;   /* initializing integer variables that would be used to compare data later in the function */
	
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
	printf( "f to shoot laser\naction: " );
	
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
				
				printf( "\033[0m" );   /* change font color back to default color basically a reset button)*/
			}
		}
		printf( "\n" );   /* re-occuring from the 'prtArr()' function */
	}
}

/* the following function shows laser being hit by the player (returning an integer) */
int shoot( int **array, int arow, int acol, int pr, int pc, char pd, int er, int ec )
{
	int sym1, sym2;   /* initializing integer variable that would be used to define type of symbol later in the function */
	int output;   /* initializing integer variable that would be used to output data later in the function */
	
	sym1 = '-';   /* defining symbol 1 to be '-' */
	sym2 = '|';   /* defining symbol 1 to be '|' */
	output = 1;   /* pre-set value of output set to 1 */
	
	system( "clear" );   /* clears the terminal window */
	
	if( pd == 'r' )   /* in the case the players direction is right-aligned */
	{
		for( pc = pc; pc < acol - 1; pc++ )   /* keep incrementing the player column value until it reaches the second-last value (ie. just before play map boundary) */
		{
			array[pr][pc+1] = sym1;   /* adds symbol 1 into the column next to the player column */
			if( array[er][ec] == sym1 )   /* if the symbol or 'laser' hits the enemy */
			{
				array[er][ec-1] = ' ';   /* erases the laser before the enemy column to make it disappear in play map */
				win( array, arow, acol, er, ec );   /* initializes the win() function to win the game */
				output = 0;   /* new 'output' value is '0' which will be returned by the function */
				pc = acol - 2;   /* this is done to break from the loop as no more increments can take place and the game has ended */
			}
			else   /* in case the enemy is still alive in play map */
			{
				redPrint( array, arow, acol, pr, pc+1 );   /* prints the play map with the laser in red color using the redPrint() function */
				array[pr][pc+1] = ' ';   /* erases the laser before printing it in next column to make it disappear in play map */
				newSleep( 0.5 );   /* makes the terminal sleep for 0.5 seconds using the newSleep() function in newSleep.c */
				system( "clear" );   /* clears the terminal window */
			}
		}
	}
	else if( pd == 'l' )   /* in the case the players direction is left-aligned */
	{		
	/* the following lines of code perform the same function as lines 79-99 explained above with only decrements taking place instead of increments */
		for( pc = pc; pc > 1; pc-- )
		{
			array[pr][pc-1] = sym1;
			if( array[er][ec] == sym1 )
			{
				array[er][ec+1] = ' ';
				win( array, arow, acol, er, ec );   /* initializing the win() function */
				output = 0;   /* specific value for 'output' meaning the game has ended */
				pc = 1;   /* ends the decrement loop */
			}
			else
			{
				redPrint( array, arow, acol, pr, pc-1 );
				array[pr][pc-1] = ' ';
				newSleep( 0.5 );
				system( "clear" );
			}
		}
	}
	else if( pd == 'u' )   /* in the case the players direction is upwards */
	{	
	/* the following lines of code perform the same function as lines 79-99 explained above with only decrements taking place instead of increments */
		for( pr = pr; pr > 1; pr-- )
		{
			array[pr-1][pc] = sym2;   /* symbol 2 is used in this case since the laser is travelling upwards */
			if( array[er][ec] == sym2 )
			{
				win( array, arow, acol, er, ec );
				output = 0;
				pr = 1;
			}
			else
			{
				redPrint( array, arow, acol, pr-1, pc );
				array[pr-1][pc] = ' ';
				newSleep( 0.5 );
				system( "clear" );
			}
		}
	}
	else if( pd == 'd' )   /* in the case the players direction is downwards */
	{	
	/* the following lines of code perform the same function as lines 79-99 explained above with only decrements taking place */	
		for( pr = pr; pr < arow - 1; pr++ )
		{
			array[pr+1][pc] = sym2;
			if( array[er][ec] == sym2 )
			{
				win( array, arow, acol, er, ec );
				output = 0;
				pr = arow - 2;
			}
			else
			{
				redPrint( array, arow, acol, pr+1, pc );
				array[pr+1][pc] = ' ';
				newSleep( 0.5 );
				system( "clear" );
			}
		}
	}
	
	return output;   /* 'output' is the variable that is returned by this function; having a value of 0 if the game has ended and having a value of 1 if the game is still running */
	
}

/* the following function declares that the user has won the game (returning nothing) */
void win( int **array, int row, int col, int er, int ec )
{
	array[er][ec] = 'X';   /* the enemy tank is now replaced with 'X' indicating that it has died */
	prtArr( array, row, col );   /* prints the array using the function prtArr() */
	printf( "You Win !!!\n" );   /* prints statement informing user that they have won the game */
}
