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

bool isValid(game *othello, int i, int j, char direction[3]) //Functions checks for a valid move from the tile board[i][j]
{
    int r, c;
    if(othello->board[i][j]=='N') //New tokens can only be placed on neutral tiles
    {
        //We check for a valid move in all 8 directions
        if(strcmp(direction,"A")==0 || strcmp(direction, "N")==0)
        {
            if (othello->board[i - 1][j] == othello->nextPlayer->colour)//North
            {
                r = i - 1;
                c = j;
                while ((othello->board[r][c] == othello->nextPlayer->colour) &&
                       r > 0) //tracing a straight line until friendly or neutral tile is reached
                    r--;
                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true; //can return true immediately after a single valid move is found
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "NE")==0)
        {
            if (othello->board[i - 1][j + 1] == othello->nextPlayer->colour)//North-East
            {
                r = i - 1;
                c = j + 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 0 && c < 7) {
                    r--;
                    c++;
                }
                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "E")==0)
        {
            if (othello->board[i][j + 1] == othello->nextPlayer->colour)//East
            {
                r = i;
                c = j + 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && c < 7)
                    c++;

                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "SE")==0)
        {
            if (othello->board[i + 1][j + 1] == othello->nextPlayer->colour)//South-East
            {
                r = i + 1;
                c = j + 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 8 && c < 7) {
                    r++;
                    c++;
                }
                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "S")==0)
        {
            if (othello->board[i + 1][j] == othello->nextPlayer->colour)//South
            {
                r = i + 1;
                c = j;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 0 && c < 7)
                    r++;

                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "SW")==0)
        {
            if (othello->board[i + 1][j - 1] == othello->nextPlayer->colour)//South-West
            {
                r = i + 1;
                c = j - 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 8 && c < 0) {
                    r++;
                    c--;
                }
                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "W")==0)
        {
            if (othello->board[i][j - 1] == othello->nextPlayer->colour)//West
            {
                r = i;
                c = j - 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && c < 0)
                    c--;

                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }

        if(strcmp(direction,"A")==0 || strcmp(direction, "NW")==0)
        {
            if (othello->board[i - 1][j - 1] == othello->nextPlayer->colour)//North-West
            {
                r = i - 1;
                c = j - 1;
                while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 0 && c < 0) {
                    r--;
                    c--;
                }
                if (othello->board[r][c] == othello->currentPlayer->colour)
                    return true;
            }
        }
    }
    return false; //Returns false if there are no valid moves from this tile
}

bool validMoves(game* othello) //Returns false if there are no valid moves for current player
{
    int i,j;

    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if(isValid(othello, i,j, "A"))
                return true; //Function returns true as soon as a valid move is found
        }
    }

    return false; //This only triggers if there are no valid moves in any direction from any tile for current player
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