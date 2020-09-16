/* game.c */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "colors.h"
#include "gamefuncs.h"

// Main Function:
int main() {
    int x = 0, y = 0;

    // initilize the window and set some settings.
    initscr();
    noecho();
    curs_set(FALSE);

		// initialize colors
		if (has_colors() == FALSE) {
			endwin();
			puts("Your terminal does not support color");
			exit(1);
		}
		start_color();
		init_colorpairs();

    // print the game rules.
    print_rules();

    // 2D int array that holds the game state.
    int gameBoard[ROW][COLUMN] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
    // Game loop:
    while(1) {
        // generate a random number 1-10:
        //   ==> if 1-6, spawn a 2 randomly on the board. 
        //   ==> if 7-10, spawn a 4 randomly on the board.
        (rand_between(1,10) <= 8) ? new_random_tile(2, gameBoard) : new_random_tile(4, gameBoard);

        // print out the game state.
        print_board(gameBoard);

        // get the players move.
        char move = get_move();
        // alter the board based on the move. (wasd)
        if(move == 'w') { // up
            move_up(gameBoard);
        }
        else if(move == 'a') { // left
            move_left(gameBoard);
        }
        else if (move == 's') { // down
            move_down(gameBoard);
        }
        else if(move == 'd') { // right
            move_right(gameBoard);
        }
    }
}