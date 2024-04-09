#define _LASER_TANK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "movement.h"
#include "newSleep.h"

int main(int argc, char* argv[])
{
	int** array = NULL;   /* initializing an array called 'array' */
	int r, c, pr, pc, er, ec;   /* initializing variables for array row, array column, player row, player column, enemy row and enemy column respectively */
	char *pd = NULL, *ed = NULL;   /* initializing character pointers to point to player directiona dn enemy direction */
	int ro, op, new, temp;   /* initialising integer variables that will be assigned a specific value later in the program */
	int i, ii, iii;   /* initialising integer variables that would be used to compare data later in the program */
	char opt;   /* initialising character variable that will be assigned a specific value later in the program */
	
	/* the following lines of code will assign respective command line inputs to the respective variable such as array row, array column etc. (see line 12) */
	r = atoi( argv[1] );   /* 'atoi' function changes character data to integer data */
	c = atoi( argv[2] );
	pr = atoi( argv[3] );
	pc = atoi( argv[4] );
	pd = argv[5];
	er = atoi( argv[6] );
	ec = atoi( argv[7] );
	ed = argv[8];

	temp = 1;   /* assumes play map dimensions are correct and player and enemy are still alive (ie. game is running) */
	
	/* the following lines of code check whether the array dimensions are within the required range */
	if( r < 5 || r > 25 || c < 5 || c > 25 )
	{
		printf( "Play map dimensions must be between 5 and 25.\n" );   /* Error message incase play map dimensions are out of bounds */
		temp = 0;   /* does not initialize the function and does not run the game (seen later in program) */
	}
	
	/* the following lines of code check whether the player and enemy coordinates are within the row and column ranges */
	if( pr < 1 || pr > r || pc < 1 || pc > c )
	{
		printf( "Player coordinates out of play map.\n" );
		temp = 0;
	}
	
	if( er < 1 || er > r || ec < 1 || ec > c )
	{
		printf( "Enemy coordinates out of play map.\n" );
		temp = 0;
	}
		
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
	
	while( temp == 1 )   /* condition to run the program as long as accurate row and column size are given and player and enemy are within them (see lines 31-49) */
	{
		/* the following lines of code add the player into the play map using the player coordinates provided */
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
		else   /* in the case no accurate direction is given the default right-aligned direction is chosen */
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

		while( opt != 'f' && op != 'b' )   /* run the next lines of code as long as the option selected is not 'f' and the value of op is not 'b' */
		{
			system( "clear" );   /* clears the terminal window */
			
			new = move( array, r, c, &pr, &pc, er, ec, opt, pd, ed );   /* moves the player in the map with respect to the type of option selected and returns a value 'a' if the player has been killed into 'new' */
			
			if( new == 'a' )   /* if player has been killed proceed with next lines of code */
			{
				op = 'b';   /* gives 'op' a value of 'b' whereby the code (line 122) would break */
				temp = 0;   /* gives 'temp' a value of 0 whereby the code (line 76) would break and the program would not carry on anymore */
			}
			
			if( op != 'b' )   /* as long as the program is running (ie. the player is still alive)... */
			{
				opt = menu();   /* ...print the option menu and pass the selected option into 'opt' */
			}
		}
				
		if( opt == 'f' )   /* if the selected option is 'f'... */
		{
			temp = shoot( array, r, c, pr, pc, *pd, er, ec );   /* ...initialize the shoot function and pass the output to 'temp' */
			if( temp == 1 )   /* as long as the enemy is not dead, the game continues */
			{
				opt = '0';   /* assign 'opt' a value of 0 to prevent continuous looping from occuring within the player map and restart from line 122 */
			}
		}
		else if( opt != ( 'w' || 's' || 'a' || 'd' || 'f' ) )   /* if the selected option is not 'w', 's', 'a', 'd' or 'f'...) */
		{
			opt = '0';   /* ignore the option and restart from line 122 */
		}
	}
	
	for( iii = 0; iii < r; iii++ )   /* the value of 'iii' starts from 0 and increments as long as it stays less than or equal to the amount of array rows */
	{
		free( array[iii] );   /* free's the heap memory located using malloc for the array  rows */
	}
	free( array );   /* free's the heap memory located using malloc for the array */
	
	return 0;
}
