CC=gcc
CFLAGS=-g -lrt -lm -Wall -Werror -fopenmp
EXE=-o run

all:
		$(CC) $(CFLAGS) $(EXE) main.c
