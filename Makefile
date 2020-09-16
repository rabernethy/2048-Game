# Makefile
CFLAGS= -I. -L.
LDFLAGS=-lncurses
CC = gcc
DEPS = colors.h
OBJ = colors.o game.o

%.o: %.c %(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)


all: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
