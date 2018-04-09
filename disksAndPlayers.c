#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disksAndPlayers.h"

void initializePlayers(player *player1, player *player2)
{
  int nameSize;
  int colorChoice;

  //ask player one for the name and replace \n with \0
  printf("What is the name of player one?\n");
  fgets(player1->name, 20, stdin);
  nameSize = strlen(player1->name);
  player1->name[nameSize -1] = '\0';

  //ask player 2 for the name and replace \n with \0
  printf("What is the name of player two?\n");
  fgets(player2->name, 20, stdin);
  nameSize = strlen(player2->name);
  player2->name[nameSize - 1] = '\0';

  //ask one of the player to choose a colour
  do {
    printf("%s, what colour would you like to be?(WHITE = 0, BLACk = 1)\n", player1->name);
    scanf("%d", &colorChoice);
  } while(colorChoice != 0 && colorChoice != 1);

  //assign colours to players depending on the choice
  if (colorChoice == 1)
  {
    player1->type = BLACK;
    player2->type = WHITE;

    printf("player1 %d\n", player1->type);
    printf("player2 %d\n", player2->type);
  }
  else
  {
    player1->type = WHITE;
    player2->type = BLACK;

    printf("player1 %d\n", player1->type);
    printf("player2 %d\n", player2->type);
  }
  //assign the points to each player:
  player1->points = 2;
  player2->points = 2;
}

void initializeBoard(disk board [SIZE][SIZE], player player1, player player2)
{
  int i, j;
  //board initialization
  for(i = 0; i < SIZE; i++)//control of rows
  {
    for(j = 0; j < SIZE; j++) //control of columns
    {
      if(i == 3)//row 3
      {
        if(j == 3){ //column 3
          board[i][j].type = player1.type;
        }
        else if (j == 4){ //column 4
          board[i][j].type = player2.type;
        }
        else{
          board[i][j].type = NONE;
        }
      }
      else if (i == 4)//row 4
      {
        if (j == 3){ //column 3
          board[i][j].type = player2.type;
        }
        else if (j == 4){ //column 4
          board[i][j].type = player1.type;
        }
        else {
          board[i][j].type = NONE;
        }
      }
      else {
        board[i][j].type = NONE;
      }
      board[i][j].pos.row = i;
      board[i][j].pos.col = j;
    }
  }
}

void printBoard(disk board[SIZE][SIZE])
{
  int i, j;
  j = 0;

  printf("\n    ");

  for(i = 0; i < SIZE; i++)
  {
    printf("%d   ",i+1);//print numbers on the x axis
  }
  for(i = 0; i < SIZE; i++)
  {
    printf("\n%d | ", i+1); //print numbers on the y axis

    for(j=0;j<SIZE; j++)
    {
      switch(board[i][j].type)
      {
        case BLACK:
          printf("1 | ");
          break;
        case WHITE:
          printf("0 | ");
          break;
        case NONE:
          printf("x | ");
          break;
        default:
          break;
      }
    }
  }
  printf("\n");
}

// void playGame()
// {
// }
//
// void finalResult()
// {
// }
