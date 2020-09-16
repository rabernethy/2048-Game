# Makefile
CFLAGS= -I. -L.
LDFLAGS=-lncurses
CC = gcc
DEPS = colors.h gamefuncs.h
OBJ = colors.o game.o gamefuncs.o

%.o: %.c %(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)


all: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
