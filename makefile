CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJS = LaserTank.o functions.o movement.o mirrors.o linkedlist.o newSleep.o
CC = gcc
EXEC = laserTank

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	
LaserTank.o : LaserTank.c functions.h movement.h mirrors.h linkedlist.h newSleep.h
	$(CC) $(CFLAGS) -c LaserTank.c

functions.o : functions.c functions.h movement.h mirrors.h linkedlist.h newSleep.h
	$(CC) $(CFLAGS) -c functions.c
	
movement.o : movement.c movement.h functions.h mirrors.h linkedlist.h newSleep.h
	$(CC) $(CFLAGS) -c movement.c

mirrors.o : mirrors.c mirrors.h functions.h movement.h linkedlist.h newSleep.h
	$(CC) $(CFLAGS) -c mirrors.c
	
linkedlist.o : linkedlist.c linkedlist.h functions.h movement.h mirrors.h newSleep.h
	$(CC) $(CFLAGS) -c linkedlist.c
	
newSleep.o : newSleep.c newSleep.h functions.h movement.h mirrors.h linkedlist.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f $(OBJS) $(EXEC)
