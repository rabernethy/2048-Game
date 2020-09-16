#ifndef HEADER_GAMEFUNCS
#define HEADER_GAMEFUNCS

#define ROW 4
#define COLUMN 4
#define DELAY 15000

// Print functions:
void print_board(int gameBoard[ROW][COLUMN]);
void print_with_spacing(int tile, int x, int y);
void print_rules(void);
// Boolean functions:
int has_empty_space(int gameBoard[ROW][COLUMN]);
int isLowercase(char c);
int isUppercase(char c);
// Game action functions:
void new_random_tile(int tile, int gameBoard[ROW][COLUMN]);
char get_move(void);
void game_over(int gameBoard[ROW][COLUMN]);
// Calculation functions:
int score(int gameBoard[ROW][COLUMN]);
int rand_between(int min, int max);
int numUnitPlaces(int n);
// Character functions:
char toLowercase(char c);
char toUppercase(char c);
// Move functions:
void move_up(int gameBoard[ROW][COLUMN]);
void move_left(int gameBoard[ROW][COLUMN]);
void move_down(int gameBoard[ROW][COLUMN]);
void move_right(int gameBoard[ROW][COLUMN]);
#endif

