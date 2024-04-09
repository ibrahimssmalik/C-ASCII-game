#define _DEFAULT_SOURCE
#include <time.h>
#include "newSleep.h"
#include "functions.h"
#include "movement.h"
#include "mirrors.h"
#include "linkedlist.h"

/* this function allows the terminal to sleep for a specified amount of time (ie. a float value) (returning nothing) */
void newSleep( float sec )
{
	struct timespec ts;
	ts.tv_sec = ( int ) sec;
	ts.tv_nsec = ( sec - ( ( int ) sec ) ) * 1000000000;
	nanosleep( &ts, NULL );
}
