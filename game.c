/*
Author: Russell Abernethy
Last Updated: 9/15/20
Desc: 2048 game
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants:
#define ROW 4
#define COLUMN 4

// Function Prototypes:
// Print functions:
void print_board(int gameBoard[ROW][COLUMN]);
// Boolean functions:
int has_empty_space(int gameBoard[ROW][COLUMN]);
int isLowercase(char c);
int isUppercase(char c);
// Game action functions:
void new_random_tile(int tile, int gameBoard[ROW][COLUMN]);
char get_move();
void game_over(int gameBoard[ROW][COLUMN]);
// Calculation functions:
int score(int gameBoard[ROW][COLUMN]);
int rand_between(int min, int max);
// Character functions:
char toLowercase(char c);
char toUppercase(char c);
// Move functions:
void move_up(int gameBoard[ROW][COLUMN]);
void move_left(int gameBoard[ROW][COLUMN]);
void move_down(int gameBoard[ROW][COLUMN]);
void move_right(int gameBoard[ROW][COLUMN]);

// Main Function:
int main() {
    // 2D int array that holds the game state.
    int gameBoard[ROW][COLUMN] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // Print the game instructions.
    printf("Instructions: \n");

    // Game loop:
    while(1) {

        // generate a random number 1-10:
        //   ==> if 1-6, spawn a 2 randomly on the board. 
        //   ==> if 7-10, spawn a 4 randomly on the board.
        (rand_between(1,10) <= 6) ? new_random_tile(2, gameBoard) : new_random_tile(4, gameBoard);

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

/*
print_board()
    desc: 
        ==> prints out the current game state.
    inputs: 
        ==> gameBoard: a 2d array that contains the game state.
*/
void print_board(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COLUMN; j++) {
            printf("%d",gameBoard[i][j]);
        } printf("\n");
    } 
    printf("\n");
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
    printf("\n\nGame Over!\nFinal Score: %d.\n", score(gameBoard));
    exit(1);
}

/*
get_move()
    desc:
        ==> gets the player's move and returns it.
    output:
        ==> returns either w, a, s, or, d.
*/
char get_move() {
    char input;
    do {
        scanf("%c", &input);
    } while (input != 'w' && input != 'W' &&input != 'a' &&input != 'A' &&input != 's' &&input != 'S' &&input != 'd' &&input != 'D');
    return toLowercase(input);
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
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_up(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < COLUMN; i++) {
        for(j = 1; j < ROW; j++) {
            if(gameBoard[j-1][i] == 0 && gameBoard[j][i] != 0) {
                gameBoard[j-1][i] = gameBoard[j][i];
                gameBoard[j][i] = 0;
                move_up(gameBoard);
            }
        }
    }
    
}

/*
move_left()
    desc:
        ==> goes row by row and shifts tiles to the left.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_left(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for(j = 1; j < COLUMN; j++) {
            if(gameBoard[i][j-1] == 0 && gameBoard[i][j] != 0) {
                gameBoard[i][j-1] = gameBoard[i][j];
                gameBoard[i][j] = 0;
                move_left(gameBoard);
            }
        }
    }
}

/*
move_down()
    desc:
        ==> goes column by column and shifts tiles down.
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_down(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < COLUMN; i++) {
        for(j = ROW - 1; j > 0; j--) {
            if(gameBoard[j+1][i] == 0 && gameBoard[j][i] != 0) {
                gameBoard[j+1][i] = gameBoard[j][i];
                gameBoard[j][i] = 0;
                move_down(gameBoard);
            }
        }
    }
    
}

/*
move_right()
    desc:
        ==> goes row by row and shifts tiles to the right. 
    input:
        ==> gameBoard: a 2d array that contains the game state.
*/
void move_right(int gameBoard[ROW][COLUMN]) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for(j = COLUMN - 2; j >= 0; j--) {
            if(gameBoard[i][j+1] == 0 && gameBoard[i][j] != 0) {
                gameBoard[i][j+1] = gameBoard[i][j];
                gameBoard[i][j] = 0;
                move_right(gameBoard);
            }
        }
    }
}