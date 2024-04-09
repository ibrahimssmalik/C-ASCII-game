#ifndef HEADER_MOVE
#define HEADER_MOVE

int move( int **array, int row, int col, int *playr, int *pplayc, int er, int ec, char option, char *playDire, char *enemDire );

int lose( int **array, int row, int col, int pr, int pc, int er, int ec, char ed );

int kill( int **array, int row, int col, int pr, int pc, char pd, int er, int ec );

#endif
