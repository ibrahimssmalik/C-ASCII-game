#define _MOVEMENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "functions.h"
#include "newSleep.h"

/* the following function moves the player based on the option selected (returning an integer) */
int move( int **array, int row, int col, int *playr, int *playc, int er, int ec, char option, char *playDire, char *enemDire )
{	
	int **pr, **pc;   /* initializing double pointers to the player row and column coordinates respectively */
	int ret, check, check2;   /* initializing integer variables that would be used to compare data later in the function */
	
	pr = &playr;   /* making 'pr' point to the player row */
	pc = &playc;   /* making 'pc' point to the player column */
	
	check = 0;   /* setting up initial value to 0 */
	check2 = 0;   /* setting up initial value to 0 */
	ret = 0;   /* setting up initial value to 0 */

	if( option == 'w' && *playDire == 'u' )   /* in the case the option selected is to move up (ie. 'w') and the player direction is already upwards */
	{
		if( **pr - 1 != 0 )   /* in the case the player row is not 0 (ie. not equal to play map boundary) */
		{
			array[**pr-1][**pc] = '^';   /* prints the new player above the old player */
			array[**pr][**pc] = ' ';   /* erases the previous player */
			**pr = **pr - 1;   /* updates the player row */
			check = lose( array, row, col, **pr, **pc, er, ec, *enemDire );   /* check whether the player has died by moving in front of the enemy and passes output into 'check' (0 if still alive and 1 if died) */
			if( check != 1 )   /* in the case the player is still alive */
			{
				check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );   /* check whether the player is directly around the enemy in which case the player wins and game ends (0 if still alive and 1 if died) */
			}
		}
	}
	else if( option == 'w' && *playDire != 'u' )   /* in the case the option selected is to move up (ie. 'w') and the player direction is not upwards */
	{
		array[**pr][**pc] = '^';   /* prints the player facing upwards in old player coordinates */
		*playDire = 'u';   /* changes player direction to upwards permanently */
		check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );   /* check whether the player is directly around the enemy in which case the player wins and game ends (0 if still alive and 1 if died) */
	}
	/* the following lines of code are repeated in the same way as above with only changes made to the options selected, player directions and coordinates */
	else if( option == 's' && *playDire == 'd' )
	{
		if( **pr + 1 != row )
		{
			array[**pr+1][**pc] = 'v';
			array[**pr][**pc] = ' ';
			**pr = **pr + 1;
			check = lose( array, row, col, **pr, **pc, er, ec, *enemDire );
			if( check != 1 )
			{
				check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
			}
		}
	}
	else if( option == 's' && *playDire != 'd' )
	{
		array[**pr][**pc] = 'v';
		*playDire = 'd';
		check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
	}
	
	else if( option == 'a' && *playDire == 'l' )
	{
		if( **pc - 1 != 0 )
		{
			array[**pr][**pc-1] = '<';
			array[**pr][**pc] = ' ';
			**pc = **pc - 1;
			check = lose( array, row, col, **pr, **pc, er, ec, *enemDire );
			if( check != 1 )
			{
				check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
			}
		}
	}
	else if( option == 'a' && *playDire != 'l' )
	{
		array[**pr][**pc] = '<';
		*playDire = 'l';
		check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
	}
	
	else if( option == 'd' && *playDire == 'r' )
	{
		if( **pc + 1 != col )
		{
			array[**pr][**pc+1] = '>';
			array[**pr][**pc] = ' ';
			**pc = **pc + 1;
			check = lose( array, row, col, **pr, **pc, er, ec, *enemDire );
			if( check != 1 )
			{
				check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
			}
		}
	}
	else if( option == 'd' && *playDire != 'r' )
	{
		array[**pr][**pc] = '>';
		*playDire = 'r';
		check2 = kill( array, row, col, **pr, **pc, *playDire, er, ec );
	}

	if( check != 1 && check2 != 1 )   /* in the case the player has not been killed and neither has the enemy */
	{
		prtArr( array, row, col );   /* print the array with updated player coordinates using the prtArr() function in functions.c */
	}
	else if( check == 1 || check2 == 1 )   /* in the case either the player has been killed or the enemy has been killed */
	{
		ret = 'a';   /* set the 'ret' value as 'a' signaling the end of the game */
	}
	
	return ret;   /* 'ret' output of the function (0 if game still running and 'a' if game has ended */
}

/* the following function checks whether the player is in the enemy's direction and killing the player in that case (returning an integer) */
int lose( int **array, int row, int col, int pr, int pc, int er, int ec, char ed )
{
	int sym1, sym2;   /* initializing integer variables that would be used to store symbols later in the function */
	int check;   /* initializing integer variables that would be used to output data */
	
	sym1 = '-';   /* assigning '-' to be the first symbol */
	sym2 = '|';   /* assigning '|' to be the second symbol */
	check = 0;   /* setting up initial value to 0 */
	
	if( ed == 'l' && er == pr && ec > pc )   /* in the case the enemy direction is left-aligned and the enemy and player are in the same row and the enemy is towards the right of the player (ie. has a higher column number) */
	{
		for( ec = ec; ec > pc+1 ; ec-- )   /* keep incrementing the enemy column value until it reaches the second-last value (ie. just before play map boundary) */
		{
			array[er][ec-1] = sym1;   /* adds symbol 1 into the column before the enemy column */
			redPrint( array, row, col, er, ec-1 );   /* prints the play map with the laser in red color using the redPrint() function in functions.c */
			array[er][ec-1] = ' ';   /* erases the laser before printing it in new column to make it disappear in play map */
			newSleep( 0.5 );   /* makes the terminal sleep for 0.5 seconds using the newSleep() function in newSleep.c */
			system( "clear" );   /* clears the terminal window */
		}
		array[pr][pc] = 'X';   /* since the player has died, replace it with 'X' */
		prtArr( array, row, col );   /* print the array with the dead player using the prtArr() function in functions.c */
		printf( "You Lose !!!\n" );   /* prints statement informing user that they have lost the game */
		check = 1;   /* new output value is '1' which will be returned by the function */
	}
	/* the following lines of code are repeated in the same way as above with only changes made to the enemy directions and coordinates */
	else if( ed == 'r' && er == pr && ec < pc )
	{
		for( ec = ec; ec < pc-1; ec++ )
		{
			array[er][ec+1] = sym1;
			redPrint( array, row, col, er, ec+1 );
			array[er][ec+1] = ' ';
			newSleep( 0.5 );
			system( "clear" );
		}
		array[pr][pc] = 'X';
		prtArr( array, row, col );
		printf( "You Lose !!!\n" );
		check = 1;
	}
	else if( ed == 'u' && ec == pc && er > pr )
	{
		for( er = er; er > pr+1; er-- )
		{
			array[er-1][ec] = sym2;
			redPrint( array, row, col, er-1, ec );
			array[er-1][ec] = ' ';
			newSleep( 0.5 );
			system( "clear" );
		}
		array[pr][pc] = 'X';
		prtArr( array, row, col );
		printf( "You Lose !!!\n" );
		check = 1;
	}
	else if( ed == 'd' && ec == pc && er < pr )
	{
		for( er = er; er < pr-1; er++ )
		{
			array[er+1][ec] = sym2;
			redPrint( array, row, col, er+1, ec );
			array[er+1][ec] = ' ';
			newSleep( 0.5 );
			system( "clear" );
		}
		array[pr][pc] = 'X';
		prtArr( array, row, col );
		printf( "You Lose !!!\n" );
		check = 1;
	}
	
	return check;   /* 'check' output of the function (0 if game still running and 1 if game has ended (ie. player has lost) */
}

/* the following function checks whether the player is directly in front of the enemy and killing the enemy in that case (returning an integer) */
int kill( int **array, int row, int col, int pr, int pc, char pd, int er, int ec )
{
	int check;   /* initializing integer variables that would be used to output data */
	
	check = 0;   /* setting up initial value to 0 */
	
	if( pd == 'r' && pc == ( ec - 1 ) && pr == er )   /* in the case the player direction is right-aligned and the player's column is just before the enemy's column and they are in the same rows */
	{
		win( array, row, col, er, ec );   /* initializes the win() function in functions.c to win the game */
		check = 1;   /* new 'check' value is '1' which will be returned by the function */
	}
	/* the following lines of code are repeated in the same way as above with only changes made to the player directions and coordinates  */
	else if( pd == 'l' && pc == ( ec + 1 ) && pr == er )
	{
		win( array, row, col, er, ec );
		check = 1;
	}
	else if( pd == 'u' && pr == ( er + 1 ) && pc == ec )
	{
		win( array, row, col, er, ec );
		check = 1;
	}
	else if( pd == 'd' && pr == ( er - 1 ) && pc == ec )
	{
		win( array, row, col, er, ec );
		check = 1;
	}
	
	return check;   /* 'check' is output of the function (0 if game still running and 1 if game has ended (ie. player has won) */
}
