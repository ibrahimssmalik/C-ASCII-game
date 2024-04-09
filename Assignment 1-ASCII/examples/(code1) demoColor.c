#include <stdio.h>
#include <stdlib.h>

/*
This file provides an example on how to use ANSI color to modify output color from printf to the terminal.
This is not a complete list of the colors. You need to do a bit of     research about "ANSI color in C".
*/

void redPrint(char* sentence)
{
  printf("\033[0;31m");	/* change font color into red color for the oncoming printf function */
  printf("%s", sentence);
  printf("\033[0m");		/* change font color back to default color (basically a reset button)*/
}

int main()
{
	redPrint("This should be red\n");
	printf("This should be default color\n");
	return 0;
}
