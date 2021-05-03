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

    game* gamePtr = &othello; //Pointer to our board for use in functions

    printBoard(gamePtr); //Print initial state of board

    bool valid = false, gameOver = false; //Keeps track of when the game ends
    char x_in;
    int x_out, y_in, y_out; //The inputted coordinates are assigned to x_in and y_in, then cast to array indices as x_out and y_out for use in functions

    while(!gameOver) //Gameplay loop begins
    {
        valid = false;
        printf("\nIt is now %s's turn.\n", othello.currentPlayer->name);
        if(validMoves(gamePtr))//First check if current player has any possible moves
        {
            while(!valid)
            {
                printf("Please enter your move in ld format (letter, digit):  ");
                fflush(stdin);
                scanf("%c%d", &x_in, &y_in);
                if(x_in>='a' && x_in<='h' && y_in>=1 && y_in<=8)//input is a board coordinate
                {
                    x_out = 7 - ('h'-x_in); //Cast board coordinates...
                    y_out = y_in - 1;       //...to array indices
                    if(othello.board[y_out][x_out]=='N' && isValid(gamePtr, y_out, x_out, "A")) //If the move is valid...
                    {
                        move(gamePtr, y_out, x_out); //...put it into effect...
                        printBoard(gamePtr);         //...print the current state of the board...
                        valid = true;                //...and validate the move
                    }
                }

                if(!valid) //If a valid input and move is not detected...
                    printf("\nError: Invalid move. Please try again.\n");//...prompt user to enter a new move
            }
            playerSwap(gamePtr); //Changes to next player
        }

        else //If no valid moves available, player's turn is passed
        {
            printf("No moves available. Passing turn...\n");
            playerSwap(gamePtr); //Changes players
            if(!validMoves(gamePtr)) //Checks if other player has valid moves
                gameOver = true; //If not, the game has ended
        }

        if(othello.currentPlayer->score==0 || othello.nextPlayer->score==0)//if either player's score hits 0...
            gameOver = true; //...the game ends
    }

    endReport(&p1, &p2);
    return 0;
}
