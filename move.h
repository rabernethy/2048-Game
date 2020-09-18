#ifndef HEADER_MOVE
#define HEADER_MOVE

void move_up(int gameBoard[4][4]);
void move_left(int gameBoard[4][4]);
void move_down(int gameBoard[4][4]);
void move_right(int gameBoard[4][4]);
void mergeU(int gameBoard[4][4], int currCol, int index);
void mergeL(int gameBoard[4][4], int currRow, int index);
void mergeD(int gameBoard[4][4], int currCol, int index);
void mergeR(int gameBoard[4][4], int currRow, int index);
#endif // !HEADER_MOVE