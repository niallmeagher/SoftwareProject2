
#ifndef SOFTWAREPROJECT2_OTHELLOLIB_H
#define SOFTWAREPROJECT2_OTHELLOLIB_H

#include <stdbool.h>

#define MAX_STR_LEN 20

typedef struct {
    char colour; //'B' and 'W' for placing their tokens on board
    char team[6]; //"Black" for player1 and "White" for player2
    int score;
    char name[MAX_STR_LEN+1];
}player;

typedef struct {
    char board[8][8]; //holds the state of every tile on board
    player* currentPlayer; //points to current player
    player *nextPlayer; //points to next player
}game;

void printBoard(game*);
bool isValid(game*, int, int, char[3]);
bool validMoves(game*);
void move(game*, int, int);
void endReport(player*, player*);

#endif //SOFTWAREPROJECT2_OTHELLOLIB_H
