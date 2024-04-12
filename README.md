Ibrahim Malik
20207593
=======

## Synopsis

Official Assignment of Unix & C Programming - COMP1000
LaserTank

## File Structure

- `functions.c` and `functions.h`: Contains functions for handling game mechanics and map configurations.
- `linkedlist.c` and `linkedlist.h`: Implements a generic linked list to store map sequences.
- `mirrors.c` and `mirrors.h`: Handles mirror mechanics in the game.
- `movement.c` and `movement.h`: Manages movement of the player and enemy tanks.
- `newSleep.c` and `newSleep.h`: Provides a custom sleep function for controlling game timing.
- `map.txt`: Input text file containing the initial game configuration.
- `log.txt`: Output text file where the map sequences are logged.
- `makefile`: Compiles the program and handles dependencies.
- `LaserTank.c`: Main file containing the entry point and game loop.

## Version information

21st May 2021 - final version of assignment

## Instructions

To compile the program, run the following commands:

```bash
make
./LaserTank input.txt output.txt
```

## Usage

Upon running the program, follow the prompts to play the game. Use the arrow keys to move the player tank and the spacebar to shoot the laser.
To save the log file, press 'l' during the game.