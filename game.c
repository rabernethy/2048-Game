/*
Author: Russell Abernethy
Last Updated: 9/15/20
Desc: 2048 game
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define M 4
#define N 4

// Function Prototypes:
void print_board(int gameBoard[M][N]);
void new_random_tile(int tile, int gameBoard[M][N]);
int has_empty_space(int gameBoard[M][N]);
int score(int gameBoard[M][N]);
int rand_between(int min, int max);
void game_over(int gameBoard[M][N]);

int main() {
    // 2D int array that holds the game state.
    int gameBoard[M][N] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// Game loop:
    while(1) {

        // generate a random number 1-10:
        //   ==> if 1-6, spawn a 2 randomly on the board. 
        //   ==> if 7-10, spawn a 4 randomly on the board.
        (rand_between(1,10) <= 6) ? new_random_tile(2, gameBoard) : new_random_tile(4, gameBoard);

        // print out the game state.
        print_board(gameBoard);

        // wait for player move input.





    }
    
}

/*
print_board()
    desc: 
        ==> prints out the current game state.
    inputs: 
        ==> gameBoard: a 2d array that contains the game state.
*/
void print_board(int gameBoard[M][N]) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
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
void new_random_tile(int tile, int gameBoard[M][N]) {
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
int has_empty_space(int gameBoard[M][N]) {
    int i, j;
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
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
int score(int gameBoard[M][N]) {
    int i, j, sum = 0;
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) 
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
void game_over(int gameBoard[M][N]) {
    printf("\n\nGame Over!\nFinal Score: %d.\n", score(gameBoard));
    exit(1);
}