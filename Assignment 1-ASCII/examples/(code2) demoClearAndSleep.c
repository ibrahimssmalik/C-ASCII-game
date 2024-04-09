#include <stdio.h>
#include <stdlib.h> /* system() function is from this library */
#include "newSleep.h"

int main()
{
	int i;

	system("clear"); 	   /* Clear terminal screen in Unix */
	printf("Start sleeping\n");
	
	for( i=1 ; i<=10 ; i++ )
	{
		newSleep(0.5);	  /* sleep for n second(s). */
		system("clear");
		printf("Sleeping for %.2f second(s)\n", ((float) i) * 0.5);
	}

	printf("done!\n");

	return 0;
}
