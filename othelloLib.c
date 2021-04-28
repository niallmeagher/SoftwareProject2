#include <stdio.h>
#include<string.h>
#include "othelloLib.h"

#define MAX_STR_LEN 20

void printBoard(board* gameBoard, player* currentPlayer)
{
    if(strcmp("Black", currentPlayer->team)==0) //Current player is Black
        printf("\nScore: %s (Black)  %d:%d  %s (White)\n", currentPlayer->name, currentPlayer->score, gameBoard->nextPlayer->score, gameBoard->nextPlayer->name);

    else //Current player is White
        printf("\nScore: %s (Black)  %d:%d  %s (White)\n", gameBoard->nextPlayer->name, gameBoard->nextPlayer->score, currentPlayer->score, currentPlayer->name);

    int i,j;
    for (i=0;i<8; i++)
    {
        printf("    "); //indent the horizontal board lines
        for(j=0;j<8;j++)
        {
            printf("--- "); //Draw horizontal board lines
        }

        printf("\n%d ", i+1); //row index
        for(j=0;j<8;j++)
        {
            printf(" | "); //Draw vertical board lines

            //Print tokens that have been placed
            if(gameBoard->colour[i][j]=='B')
                printf("B");

            else if(gameBoard->colour[i][j]=='W')
                printf("W");

            else
                printf(" ");
        }

        printf(" |\n"); //Close final box of row
    }

    //Close bottom row
    printf("    "); //indent the horizontal board lines
    for(i=0;i<8;i++)
        printf("--- "); //print horizontal board lines
    //Print file index
    printf("\n  ");
    for(i=0;i<8;i++)
        printf("   %c", 'a'+i);
    printf("\n\n");
}
