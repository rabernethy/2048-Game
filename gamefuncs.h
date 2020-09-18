#ifndef HEADER_GAMEFUNCS
#define HEADER_GAMEFUNCS
int has_empty_space(int gameBoard[4][4]);
int isLowercase(char c);
int isUppercase(char c);
void new_random_tile(int tile, int gameBoard[4][4]);
char get_move(void);
int score(int gameBoard[4][4]);
int rand_between(int min, int max);
char toLowercase(char c);
char toUppercase(char c);
#endif // !HEADER_MOVE

