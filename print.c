/* print.c */

/* Written By: Russell Abernethy*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "print.h"
#include "colors.h"
#include "constants.h"
/*
print_board()
    desc: 
        ==> prints out the current game state.
    inputs: 
        ==> gameBoard: a 2d array that contains the game state.
*/
void print_board(int gameBoard[ROW][COLUMN], int score) {
    int i, j, x, y = 0;
    clear(); // clear the screen
    for (i = 0; i < ROW; i++) {
        x = 0;
        mvprintw(y,x,"---------------------------------");
        y++; //move down a line
        mvprintw(y,x,"|"); 
        x++;
        for (j = 0; j < COLUMN; j++) {
            print_with_spacing(gameBoard[i][j], x, y);
            x += 8;
        }
        y++;
    }
    mvprintw(y,0,"---------------------------------");
    y++;
    mvprintw(y,0,"Score: %d", score);
    refresh();
}

/*
print_with_spacing()
    desc: 
        ==> handles the formating required for printing the gameboard.
    input: 
        ==> tile: the integer number to be printed.
        ==> x: the x cord to print the characters at
        ==> y: the y cord to print the chracters at
*/
void print_with_spacing(int tile, int x, int y) {
    int fg, bg;
		fg = COLOR_WHITE;
		switch (tile) {
			case 2:
			case 128:
				bg = COLOR_YELLOW;
				break;
			case 4:
			case 256:
				bg = COLOR_MAGENTA;
				break;
			case 8:
			case 512:
				bg = COLOR_RED;
				break;
			case 16:
			case 1024:
				bg = COLOR_GREEN;
				break;
			case 32:
			case 2048:
				bg = COLOR_CYAN;
				break;
			case 64:
			case 4096:
				bg = COLOR_BLUE;
				break;
			default:
				bg = COLOR_BLACK;
		}
		// Set the attribute
		attron(COLOR_PAIR(colornum(fg, bg)));
		attron(A_BOLD);
        // do not print the tile if it is zero
        if (tile == 0)
            mvprintw(y, x, "       ");
        else {
		    switch (numUnitPlaces(tile)) { //format based on the number of units places in the number
            case 1:
                mvprintw(y,x,"   %d   ",tile);
                break;
            case 2:
                mvprintw(y,x,"  %d   ",tile);
                break;
            case 3:
                mvprintw(y,x,"  %d  ", tile);
                break;
            case 4: 
                mvprintw(y,x," %d  ", tile);
                break;
            case 5:
                mvprintw(y,x," %d ", tile);
                break;
            case 6:
                mvprintw(y,x,"%d ", tile);
                break;
            case 7: 
                mvprintw(y,x,"%d", tile);
                break;
            default:
                break;
            }
        }
		//Turn attribute off
		attroff(COLOR_PAIR(colornum(fg, bg)));
		attroff(A_BOLD);
		mvprintw(y,x+7,"|");
}

/*
print_rules()
    desc: 
        ==> prints the rules of the game.
*/
void print_rules() {
    clear();
    mvprintw(0,0,"Instructions: ");
    mvprintw(1,0," - use 'w' 'a' 's' and 'd' to move tiles.");
    mvprintw(2,0," - the game ends when the board fills and no move is made.");
    mvprintw(3,0," - you can press 'q' to quit.");
    refresh();
    sleep(1);
}

/*
game_over()
    desc: 
        ==> prints a message when the game is over and quits the program.
    input:
        ==> gameboard: a 2d array that contains the game state.
*/
void game_over(int gameBoard[ROW][COLUMN], int score) {
    clear();
    mvprintw(0,0,"Game Over! Final Score: %d.", score);
    refresh();
    sleep(5);
    endwin();
    exit(0);
}

/*
numUnitPlaces()
    desc: 
        ==> counts the number of unit places in an integer.
    input:
        ==> n: integer to have it's unit places counted.
    output: 
        ==> returns the number of unit places in n.
*/
int numUnitPlaces(int n) {
    if(n == 0) 
        return 1;
    int counter = 0;
    while (n != 0) {
        counter++;
        n /= 10;
    }
    return counter;
}