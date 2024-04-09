CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJS = LaserTank.o functions.o movement.o newSleep.o
CC = gcc
EXEC = laserTank

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	
LaserTank.o : LaserTank.c functions.h movement.h newSleep.h
	$(CC) $(CFLAGS) -c LaserTank.c

functions.o : functions.c functions.h movement.h newSleep.h
	$(CC) $(CFLAGS) -c functions.c
	
movement.o : movement.c movement.h functions.h newSleep.h
	$(CC) $(CFLAGS) -c movement.c
	
newSleep.o : newSleep.c newSleep.h functions.h movement.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f $(OBJS) $(EXEC)
