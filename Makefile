# Makefile

CFLAGS= -I. -L.
LDFLAGS=-lncurses
CC = gcc
DEPS = colors.h constants.h gamefuncs.h move.h print.h
OBJ = colors.o game.o gamefuncs.o move.o print.o

%.o: %.c %(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)


all: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm *.o
	rm all

run: all
	./all