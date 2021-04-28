#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include "othelloLib.h"

#define MAX_STR_LEN 20

void printBoard(game* othello)
{
    if(strcmp("Black", othello->currentPlayer->team)==0) //Current player is Black
        printf("\nScore: %s (Black)  %d:%d  %s (White)\n", othello->currentPlayer->name, othello->currentPlayer->score, othello->nextPlayer->score, othello->nextPlayer->name);

    else //Current player is White
        printf("\nScore: %s (Black)  %d:%d  %s (White)\n", othello->nextPlayer->name, othello->nextPlayer->score, othello->currentPlayer->score, othello->currentPlayer->name);

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
            if(othello->board[i][j]=='B')
                printf("B");

            else if(othello->board[i][j]=='W')
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

void endReport(player* winner, player* loser)
{
    FILE *report;

    printf("\nGenerating report...\n");
    if((report=fopen("othello-results.txt", "a"))==NULL) //Open report file to append
    {
        printf("Error opening file.\n");
        exit(0);
    }

    else
    {
        //Get time of match end
        time_t now;
        time(&now);
        struct tm *matchTime = localtime(&now); //Convert to calendar time

        //print to file
        fprintf(report, "%02d/%02d/%d\t%02d:%02d:%02d\t%s beat %s %d:%d\n", matchTime->tm_mday, matchTime->tm_mon+1, matchTime->tm_year+1900,
                matchTime->tm_hour, matchTime->tm_min, matchTime->tm_sec, winner->name, loser->name, winner->score, loser->score);
        printf("Report complete!\n");
        fclose(report);
    }
}