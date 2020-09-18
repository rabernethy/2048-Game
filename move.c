/* move.c */

/* Written By: Russell Abernethy */

#include <stdio.h>
#include "move.h"
#include "constants.h"


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
    for (i = 0; i < COLUMN; i++) 
        mergeU(gameBoard, i, 0);    
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
        mergeD(gameBoard,i,3);
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


void mergeU(int gameBoard[ROW][COLUMN], int currCol, int index) {
    int i;
    for (i = index + 1; i <= 3; i++) {

        // if the tile ahead is != 0
        if(gameBoard[i][currCol]) {
            
            // if the current tile is zero:
            if (gameBoard[index][currCol] == 0) {
                gameBoard[index][currCol] = gameBoard[i][currCol];
                gameBoard[i][currCol] = 0;
            }

            // if the tiles are the same, combine them
            else if(gameBoard[index][currCol] == gameBoard[i][currCol]) {
                gameBoard[index][currCol] *= 2;
                gameBoard[i][currCol] = 0;
                mergeU(gameBoard, currCol, index+1);
                break;
            }

            // if the tiles are different:
            else {
                // if the tile is next to the current tile, do nothing
                if(i - index > 1) {
                    gameBoard[index + 1][currCol] = gameBoard[i][currCol];
                    gameBoard[i][currCol] = 0;
                    mergeU(gameBoard,currCol, index+1);
                    break;
                }
                else {
                    mergeU(gameBoard,currCol, index+1);
                    break;
                }
            } 
        }
    }
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
        if(gameBoard[i][currCol]) {
            
            // if the current tile is zero:
            if (gameBoard[index][currCol] == 0) {
                gameBoard[index][currCol] = gameBoard[i][currCol];
                gameBoard[i][currCol] = 0;
            }

            // if the tiles are the same, combine them
            else if(gameBoard[index][currCol] == gameBoard[i][currCol]) {
                gameBoard[index][currCol] *= 2;
                gameBoard[i][currCol] = 0;
                mergeD(gameBoard, currCol, index-1);
                break;
            }

            // if the tiles are different:
            else {
                // if the tile is next to the current tile, do nothing
                if(index - i > 1) {
                    gameBoard[index - 1][currCol] = gameBoard[i][currCol];
                    gameBoard[i][currCol] = 0;
                    mergeD(gameBoard,currCol, index-1);
                    break;
                    
                }
                else {
                    mergeD(gameBoard,currCol, index-1);
                    break;
                }
            } 
        }
    }
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
                    mergeR(gameBoard,currRow, index-1);
                    break;
                }
                else {
                    mergeR(gameBoard,currRow, index-1);
                    break;
                }
            } 
        }
    }
}