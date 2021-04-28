#include <stdio.h>
#include <string.h>
#include "othelloLib.h"
#define MAX_STR_LEN 20

int main() {
    //Initialise othello and stats for p1 & p2
    player p1 = {'B', "Black", 2, ""};
    player p2 = {'W', "White", 2, ""};
    game othello = {{'N'}, &p1, &p2};

    int i,j;

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            othello.board[i][j] = 'N'; //N token means tile is neutral
        }
    }
    othello.board[3][3] = 'W';
    othello.board[4][4] = 'W';
    othello.board[3][4] = 'B';
    othello.board[4][3] = 'B';


    printf("\t\t***Welcome to Othello!***\n\n"
           "Enter name of Player 1 (Black):  ");
    fgets(p1.name,MAX_STR_LEN, stdin); //Assign name to p1
    printf("\nEnter name of Player 2 (White):  ");
    fgets(p2.name, MAX_STR_LEN, stdin); //Assign name to p2

    //Remove newline from name input
    p1.name[strcspn(p1.name, "\n")] = 0;
    p2.name[strcspn(p2.name, "\n")] = 0;

    player *currentPlayer = &p1; //Assign current player to a pointer
    player *nextPlayer = &p2; //points to next player
    game* gamePtr = &othello; //Pointer to our board for use in functions

    printBoard(gamePtr);


    return 0;
}
