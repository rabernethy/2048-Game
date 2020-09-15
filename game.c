#include <stdio.h>

#define M 4
#define N 4

void print_board(int gameBoard[M][N]);


int main() {
    // 2D int array that holds the game state.

    int gameBoard[M][N] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    print_board(gameBoard);
}

void print_board(int gameBoard[M][N]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d",gameBoard[i][j]);
        }
        printf("\n");
    }
}