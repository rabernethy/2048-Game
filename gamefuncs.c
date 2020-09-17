/* gamefuncs.c */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "gamefuncs.h"
#include "colors.h"
#include <unistd.h>

/*
print_board()
    desc: 
        ==> prints out the current game state.
    inputs: 
        ==> gameBoard: a 2d array that contains the game state.
*/
void print_board(int gameBoard[ROW][COLUMN]) {
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
    mvprintw(y,0,"Score: %d", score(gameBoard));
    refresh();
}

/*
new_random_tile()
    desc: 
        ==> add a new tile randomly.
        ==> if there is no where to place a tile, print the score and end the game.
    input:
        ==> tile: the int value that is being added to the gameboard
        ==> gameBoard: a 2d array that contains the game state.
*/
void new_random_tile(int tile, int gameBoard[ROW][COLUMN]) {
    // check if there is somewhere to place a tile.
    if(has_empty_space(gameBoard)) {
        // try to place the tile.
        int x, y, flag = 1;
        do {
            // generate coordinates for a random space on the gameBoard.
            x = rand_between(0,3);
            y = rand_between(0,3);
            // if the space is empty, place the tile there and break from the loop.
            if(gameBoard[x][y] == 0) {
                gameBoard[x][y] = tile;
                flag = 0;
            }
        } while (flag);
    }
    // Game Over!
    else {
        game_over(gameBoard);
    }
}

/*
has_empty_space()
    desc:
        ==> checks if there is an empty space to place a tile into.
    input:
        ==> gameboard: a 2d array that contains the game state.
    output:
        ==> returns 1 / TRUE if there is an empty space on the gameboard.
        ==> returns 0 / FALSE if there is no empty space on the gameboard.
*/
int has_empty_space(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for(i = 0; i < ROW; i++) {
        for(j = 0; j < COLUMN; j++) {
            if(gameBoard[i][j] == 0)
                return 1;
        }
    } 
    return 0;
}

/*
score()
    desc:
        ==> calculates current score based on the game state.
    input:
        ==> gameboard: a 2d array that contains the game state.
    output:
        ==> returns the score.
*/
int score(int gameBoard[ROW][COLUMN]) {
    int i, j, sum = 0;
    for(i = 0; i < ROW; i++) {
        for(j = 0; j < COLUMN; j++) 
            sum += gameBoard[i][j];
    }
    return sum;
}

/*
rand_between()
    desc: 
        ==> finds a random number in the range [min, max].
    inputs:
        ==> min: the lower bound.
        ==> max: the upper bound.
    output:
        ==> an integer in the range [min, max]. 
*/
int rand_between(int min, int max) {
    return rand() % (max - min + 1);
}

/*
game_over()
    desc: 
        ==> prints a message when the game is over and quits the program.
    input:
        ==> gameboard: a 2d array that contains the game state.
*/
void game_over(int gameBoard[ROW][COLUMN]) {
    clear();
    mvprintw(0,0,"Game Over! Final Score: %d.", score(gameBoard));
    refresh();
    sleep(5);
    endwin();
    exit(0);
}

/*
get_move()
    desc:
        ==> gets the player's move and returns it.
    output:
        ==> returns either w, a, s, or, d.
*/
char get_move() {
    char c;
    do {
        c = getch();
        usleep(DELAY);
    } while (c != 'w' && c != 'W' &&c != 'a' &&c != 'A' &&c != 's' &&c != 'S' &&c != 'd' &&c != 'D');
    return toLowercase(c);
}

/*
toLowercase()
    desc: 
        ==> turns an uppercase character to a lowercase character.
    input:
        ==> c: character to be converted to lowercase.
    output:
        ==> returns a lowercase character.
        ==> returns c if c wasn't an uppercase character.
*/
char toLowercase(char c) {
    if (isUppercase(c)) 
        return c + 32;
    return c;
}

/*
isLowercase()
    desc:
        ==> checks if a character is a lowercase alphabetical character.
    input:
        ==> c: character to be checked.
    output:
        ==> returns 1 / TRUE if c is lowercase.
        ==> returns 0 / FALSE otherwise.
*/
int isLowercase(char c) {
    if (c >= 97 && c <= 122)
        return 1; // TRUE
    return 0; // FALSE
}

/*
toUppercase()
    desc: 
        ==> turns a lowercase character to an uppercase character.
    input:
        ==> c: character to be converted to uppercase.
    output:
        ==> returns an uppercase character.  
        ==> returns c if c wasn't a lowercase character.
*/
char toUppercase(char c) {
    if (isLowercase(c))
        return c - 32;
    return c;
}

/*
isUppercase()
    desc:
        ==> checks if a character is a uppercase alphabetical character.
    input:
        ==> c: character to be checked.
    output:
        ==> returns 1 / TRUE if c is uppercase.
        ==> returns 0 / FALSE otherwise.
*/
int isUppercase(char c) {
    if(c >= 65 && c <= 90)
        return 1; // TRUE
    return 0; // FALSE
}

/*
move_up()
    desc:
        ==> goes column by column and shifts the tiles towards the top.
        ==> merges tiles if the same tile exists in the position about to be moved.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_up(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < COLUMN; i++) {
        for(j = 1; j < ROW; j++) {
            // if there is an empty tile
            if(gameBoard[j-1][i] == 0 && gameBoard[j][i] != 0) {
                gameBoard[j-1][i] = gameBoard[j][i];
                gameBoard[j][i] = 0;
                move_up(gameBoard);
            }
            // if the tiles are the same, merge.
            if(gameBoard[j-1][i] == gameBoard[j][i] && gameBoard[j][i] != 0) {
                gameBoard[j-1][i] *= 2;
                gameBoard[j][i] = 0;
            }
        }
    }
    
}

/*
move_left()
    desc:
        ==> goes row by row and shifts tiles to the left.
        ==> merges tiles if the same tile exists in the position about to be moved.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_left(int gameBoard[ROW][COLUMN]) {
    int i;
    for (i = 0; i < ROW; i++)
        mergeL(gameBoard, i, 0);
}

/*
move_down()
    desc:
        ==> goes column by column and shifts tiles down.
        ==> merges tiles if the same tile exists in the position about to be moved.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_down(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < COLUMN; i++) {
        for(j = ROW - 2; j >= 0; j--) {
            // if there is an empty tile
            if(gameBoard[j+1][i] == 0 && gameBoard[j][i] != 0) {
                gameBoard[j+1][i] = gameBoard[j][i];
                gameBoard[j][i] = 0;
                move_down(gameBoard);
            }
            // if the tiles are the same, merge.
            if(gameBoard[j+1][i] == gameBoard[j][i] && gameBoard[j][i] != 0) {
                gameBoard[j+1][i] *= 2;
                gameBoard[j][i] = 0;
            }
        }
    }
}

/*
move_right()
    desc:
        ==> goes row by row and shifts tiles to the right. 
        ==> merges tiles if the same tile exists in the position about to be moved.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/

void move_right(int gameBoard[ROW][COLUMN]) {
    int i;
    for (i = 0; i < ROW; i++)
        mergeR(gameBoard, i, 3);
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
    mvprintw(3,0," - you can press ctrl + z to quit.");
    refresh();
    sleep(1);
}


void mergeU(int gameBoard[ROW][COLUMN], int currCol, int index) {

}
void mergeL(int gameBoard[ROW][COLUMN], int currRow, int index) {
    int i;
    for (i = index + 1; i <= 3; i++) {

        // if the tile ahead is != 0
        if(gameBoard[currRow][i]) {

            // if the current tile is zero:
            if (gameBoard[currRow][index] == 0) {
                gameBoard[currRow][index] = gameBoard[currRow][i];
                gameBoard[currRow][i] = 0;
                
            }

            // if the tiles are the same, combine them
            else if(gameBoard[currRow][index] == gameBoard[currRow][i]) {
                gameBoard[currRow][index] *= 2;
                gameBoard[currRow][i] = 0;
                mergeL(gameBoard, currRow, index + 1);
                break;
            }

            // if the tiles are different:
            else {
                // if the tile is next to the current tile, do nothing
                if(i - index > 1) {
                    gameBoard[currRow][index + 1] = gameBoard[currRow][i];
                    gameBoard[currRow][i] = 0;
                    mergeL(gameBoard,currRow, index +1);
                    break;
                }
                else {
                    mergeL(gameBoard,currRow, index +1);
                    break;
                }
            }
        }
    }    
}

void mergeD(int gameBoard[ROW][COLUMN], int currCol, int index) {
    int i;
    for (i = index - 1; i >= 0; i--) {
        // if the tile ahead is != 0
        if(gameBoard[currCol][i] != 0) {
            // if the current tile is zero:
            if (gameBoard[currCol][index] == 0) {
                gameBoard[currCol][index] = gameBoard[currCol][i];
                gameBoard[currCol][i] = 0;
                i--;
            }
            // if the tiles are the same, combine them
            if(gameBoard[currCol][index] == gameBoard[currCol][i]) {
                gameBoard[currCol][index] *= 2;
                gameBoard[currCol][i] = 0;
            }
            // if the tiles are different:
            if (gameBoard[currCol][index] != gameBoard[currCol][i]) {
                gameBoard[currCol][index-1] = gameBoard[currCol][i];
                // handles edge case: the next tile is the tile.
                if (index - 1 != i)
                     gameBoard[currCol][i] = 0;
                break;
            }
        }
    }
    // keep running if not done.
    if(index > 0)
        mergeR(gameBoard, currCol, index - 1);
}


void mergeR(int gameBoard[ROW][COLUMN],int currRow,int index) {
    int i;
    for (i = index - 1; i >= 0; i--) {

        // if the tile ahead is != 0
        if(gameBoard[currRow][i]) {
            
            // if the current tile is zero:
            if (gameBoard[currRow][index] == 0) {
                gameBoard[currRow][index] = gameBoard[currRow][i];
                gameBoard[currRow][i] = 0;
            }

            // if the tiles are the same, combine them
            else if(gameBoard[currRow][index] == gameBoard[currRow][i]) {
                gameBoard[currRow][index] *= 2;
                gameBoard[currRow][i] = 0;
                mergeR(gameBoard,currRow, index-1);
                break;
            }

            // if the tiles are different:
            else {
                // if the tile is next to the current tile, do nothing
                if(index - i > 1) {
                    gameBoard[currRow][index - 1] = gameBoard[currRow][i];
                    gameBoard[currRow][i] = 0;
                    
                }
                else {
                    mergeR(gameBoard,currRow, index-1);
                    break;
                }
            } 
        }
    }
}