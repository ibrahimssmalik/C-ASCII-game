#ifndef HEADER_FUNCTIONS
#define HEADER_FUNCTIONS

void prtArr( int **Arr, int row, int col );

char menu( void );

void redPrint( int **array, int row, int col, int sr, int sc );

int shoot( int **array, int arow, int acol, int pr, int pc, char pd, int er, int ec );

void win( int **array, int row, int col, int er, int ec );

#endif
