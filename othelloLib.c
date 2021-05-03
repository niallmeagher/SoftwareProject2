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

    //We check for a valid move in all 8 directions
    if(strcmp(direction,"A")==0 || strcmp(direction, "N")==0) //North
    {
        if (othello->board[i - 1][j] == othello->nextPlayer->colour) {
            r = i - 1;
            c = j;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 0) //tracing a straight line until friendly or neutral tile is reached
                r--;
            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true; //can return true immediately after a single valid move is found

        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "NE")==0) //North-East
    {
        if (othello->board[i - 1][j + 1] == othello->nextPlayer->colour) {
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

    if(strcmp(direction,"A")==0 || strcmp(direction, "E")==0) //East
    {
        if (othello->board[i][j + 1] == othello->nextPlayer->colour)
        {
            r = i;
            c = j + 1;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && c < 7)
                c++;

            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "SE")==0) //South-East
    {
        if (othello->board[i + 1][j + 1] == othello->nextPlayer->colour)
        {
            r = i + 1;
            c = j + 1;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && r < 7 && c < 7)
            {
                r++;
                c++;
            }
            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "S")==0) //South
    {
        if (othello->board[i + 1][j] == othello->nextPlayer->colour)
        {
            r = i + 1;
            c = j;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && r < 7)
                r++;

            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "SW")==0) //South-West
    {
        if (othello->board[i + 1][j - 1] == othello->nextPlayer->colour)
        {
            r = i + 1;
            c = j - 1;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && r < 7 && c > 0) {
                r++;
                c--;
            }
            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "W")==0) //West
    {
        if (othello->board[i][j - 1] == othello->nextPlayer->colour)
        {
            r = i;
            c = j - 1;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && c > 0)
                c--;

            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
        }
    }

    if(strcmp(direction,"A")==0 || strcmp(direction, "NW")==0) //North-West
    {
        if (othello->board[i - 1][j - 1] == othello->nextPlayer->colour)
        {
            r = i - 1;
            c = j - 1;
            while ((othello->board[r][c] == othello->nextPlayer->colour) && r > 0 && c > 0) {
                r--;
                c--;
            }
            if (othello->board[r][c] == othello->currentPlayer->colour)
                return true;
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
            if(othello->board[i][j]=='N' && isValid(othello, i,j, "A"))
                return true; //Function returns true as soon as a valid move is found
        }
    }

    return false; //This only triggers if there are no valid moves in any direction from any tile for current player
}

void move(game* othello, int i, int j) //Effects the move player has inputted provided it is valid
{
    othello->board[i][j] = othello->currentPlayer->colour; //Place token on board
    othello->currentPlayer->score++; //Placing the token increases the player's score
    //Now see if score is changed for each direction
    int r, c;
    if(isValid(othello, i, j, "N"))  //North
    {
        r = i - 1;
        c = j;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r--][c] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "NE")) //North-East
    {
        r = i - 1;
        c = j + 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r--][c++] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "E")) //East
    {
        r = i;
        c = j + 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r][c++] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "SE")) //South-East
    {
        r = i + 1;
        c = j + 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r++][c++] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "S")) //South
    {
        r = i + 1;
        c = j;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r++][c] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "SW")) //South-West
    {
        r = i + 1;
        c = j - 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r++][c--] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "W")) //West
    {
        r = i;
        c = j - 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r][c--] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }

    if(isValid(othello, i, j, "NW")) //North-West
    {
        r = i - 1;
        c = j - 1;
        while (othello->board[r][c] == othello->nextPlayer->colour)
        {
            othello->board[r--][c--] = othello->currentPlayer->colour; //Flip the token
            othello->currentPlayer->score++; //increment current player's score
            othello->nextPlayer->score--;//decrement opposing player's score
        }
    }
}

void playerSwap(game* othello) //Swaps next player to current player and current player to next player
{
    player* tmp = othello->currentPlayer;
    othello->currentPlayer = othello->nextPlayer;
    othello->nextPlayer = tmp;
}

void endReport(player* player1, player* player2) //Prints final result to txt file
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
        fprintf(report, "%02d/%02d/%d\t%02d:%02d:%02d\t%s %d:%d %s\t\t", matchTime->tm_mday, matchTime->tm_mon+1, matchTime->tm_year+1900,
                matchTime->tm_hour, matchTime->tm_min, matchTime->tm_sec, player1->name,  player1->score, player2->score, player2->name);

        if(player1->score > player2->score) //Player 1 wins
            fprintf(report, "%s wins!\n", player1->name);

        else if(player2->score > player1->score) //Player 2 wins
            fprintf(report, "%s wins!\n", player2->name);

        else //Or else the game is a tie
            fprintf(report, "%s and %s tie!\n", player1->name, player2->name);

        printf("Report complete!\n");
        fclose(report);
    }
}