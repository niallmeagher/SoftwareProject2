#include <stdio.h>
#include <string.h>
#include "othelloLib.h"
#define MAX_STR_LEN 20

int main() {
    //Initialise gameBoard and stats for p1 & p2
    player p1 = {'B', "Black", 2, ""};
    player p2 = {'W', "White", 2, ""};
    board gameBoard = {{'N'}, &p2};

    int i,j;

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            gameBoard.colour[i][j] = 'N'; //N token means tile is neutral
        }
    }
    gameBoard.colour[3][3] = 'W';
    gameBoard.colour[4][4] = 'W';
    gameBoard.colour[3][4] = 'B';
    gameBoard.colour[4][3] = 'B';


    printf("\t\t***Welcome to Othello!***\n\n"
           "Enter name of Player 1 (Black):  ");
    fgets(p1.name,MAX_STR_LEN, stdin); //Assign name to p1
    printf("\nEnter name of Player 2 (White):  ");
    fgets(p2.name, MAX_STR_LEN, stdin); //Assign name to p2

    player *currentPlayer = &p1; //Assign current player to a pointer
    board *boardPtr = &gameBoard; //Pointer to our board for use in functions

    printBoard(boardPtr, currentPlayer);

    return 0;
}
