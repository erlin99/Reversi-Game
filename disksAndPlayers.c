#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  player1->name[0] = toupper(player1->name[0]);

  //ask player 2 for the name and replace \n with \0
  printf("What is the name of player two?\n");
  fgets(player2->name, 20, stdin);
  nameSize = strlen(player2->name);
  player2->name[nameSize - 1] = '\0';
  player2->name[0] = toupper(player2->name[0]);

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

    printf("%s --> BLACK (1)\n", player1->name);
    printf("%s --> WHITE (0)\n", player2->name);
  }
  else
  {
    player1->type = WHITE;
    player2->type = BLACK;

    printf("%s --> WHITE (0)\n", player1->name);
    printf("%s --> BLACK (1)\n", player2->name);
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
        if(j == 3) { //column 3
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

void playGame(player *player1, player *player2, disk board[SIZE][SIZE], ChoicesPtr *sPtr)
{
}

//print final result to terminal and to text file
void finalResult(player *player1, player *player2)
{
  FILE *filePtr;//pointer to rext file

  //if file cannot be created, print warning message and results to terminal
  if ((filePtr = fopen("result.txt", "w")) == NULL)
  {
    printf("Text file to store result couldn't be created.\n");

    printf("\n%s --> %d points.\n", player1->name, player1->points);
    printf("%s --> %d points.\n", player2->name, player2->points);

    //if player 1 has more points
    if (player1->points > player2->points) {
      printf("The WINNER is: %s\n", player1->name);
    }
    //if player 2 has more points
    else if (player2->points > player1->points) {
      printf("The WINNER is: %s\n", player2->name);
    }
    //in the case of a tie
    else {
      printf("It's a DRAW!\n");
    }
  }
  else
  {
    printf("\n%s --> %d points.\n", player1->name, player1->points);
    fprintf(filePtr, "Player 1: %s. Points: %d.\n", player1->name, player1->points);

    printf("%s --> %d points.\n", player2->name, player2->points);
    fprintf(filePtr, "Player 2: %s. Points: %d.\n", player2->name, player2->points);

    //if player 1 has more points
    if (player1->points > player2->points) {
      printf("The WINNER is: %s\n", player1->name);
      fprintf(filePtr, "\nThe WINNER is: %s\n", player1->name);
    }
    //if player 2 has more points
    else if (player2->points > player1->points) {
      printf("The WINNER is: %s\n", player2->name);
      fprintf(filePtr, "\nThe WINNER is: %s\n", player2->name);
    }
    //in the case of a tie
    else {
      printf("It's a DRAW!\n");
      fprintf(filePtr, "\nIt's a DRAW\n");
    }
  }

  fclose(filePtr); //close file
}

void checkMoves(disk board[SIZE][SIZE], ChoicesPtr *startPtr)
{
  int i, j, k, l;
  for(i = 0; i < SIZE; i++) //control rows
  {
    for(j = 0; j < SIZE; j++) //control columns
    {
      //checks the board for black disks
      if(board[i][j].type ==  BLACK)
      {
        //checking for possible moves to the RIGHT
        if(board[i][j+1].type == WHITE)
        {
          for(l = j+1; l < SIZE; l++)
          {
            if(board[i][l].type == NONE) {
              insertMoves(startPtr, i, l);
              break;
            }
          }
        }

        //checking for possible moves to the LEFT
        if(board[i][j-1].type == WHITE)
        {
          for(l = j-1; l >= 0; l--)
          {
            if(board[i][l].type == NONE) {
              insertMoves(startPtr, i, l);
              break;
            }
          }
        }

        //checking possible moves DOWNWARDS
        if(board[i+1][j].type == WHITE)
        {
          for(k = i+1; k < SIZE; k++)
          {
            if(board[k][j].type == NONE) {
              insertMoves(startPtr, k, j);
              break;
            }
          }
        }

        //checking possible moves UPWARDS
        if(board[i-1][j].type == WHITE)
        {
          for(k = i-1; k >= 0; k--)
          {
            if(board[k][j].type == NONE) {
              insertMoves(startPtr, k, j);
              break;
            }
          }
        }

        //checking possible moves RIGHT-DOWN DIAGONAL
        if(board[i+1][j+1].type == WHITE)
        {
          for(k = i+1, l = j+1; k < SIZE || l < SIZE; k++, l++)
          {
            if(board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              break;
            }
          }
        }

        //checking possible moves LEFT-DOWN DIAGONAL
        if(board[i+1][j-1].type == WHITE)
        {
          for(k = i+1, l = j-1; k < SIZE || l >= 0; k++, l--)
          {
            if(board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              break;
            }
          }
        }

        //checking possible moves RIGHT-UP DIAGONAL
        if(board[i-1][j+1].type == WHITE)
        {
          for(k = i-1, l = j+1; k >= 0 || l < SIZE; k--, l++)
          {
            if(board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              break;
            }
          }
        }

        //checking possible moves LEFT-UP DIAGONAL
        if(board[i-1][j-1].type == WHITE)
        {
          for(k = i-1, l = j-1; k >= 0 || l >= 0; k--, l--)
          {
            if(board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              break;
            }
          }
        }
      }
    }
  }
}

// //changes disk colour
void colourChangeBlack(coordX, coordY)//change the colours of other disks once a move is made
{
  //takes input of users move (co-ordinates, x,y)
  int x, y;

  //assigns values from user input function
  x = coordX;
  y = coordY;
  //horizontal going right
  if(board[x+1][y].type == WHITE)
  {
    int l = x+1;
    while(board[l][y].type != BLACK && board[l][y].type != NONE || l<SIZE)
    {
      board[l][y].type == BLACK;
      l++;
    }
  }
  //horizontal going left
  if(board[x-1][y].type == WHITE)
  {
    int l = x-1;
    while(board[l][y].type != BLACK && board[l][y].type != NONE || l >= 0)
    {
      board[l][y].type == BLACK;
      l--;
    }
  }
  //vertical going up
  if(board[x][y+1].type == WHITE)
  {
    int l = y+1;
    while(board[x][l].type != BLACK && board[x][l].type != NONE || l < SIZE)
    {
      board[x][l].type == BLACK;
      l++;
    }
  }
  //vertical going down
  if(board[x][y-1].type == WHITE)
  {
    int l = y-1;
    while(board[x][l].type != BLACK && board[x][l].type != NONE || l >= 0)
    {
      board[x][l].type == BLACK;
      l--;
    }
  }
}

//insert possible moves into a linked list
void insertMoves(ChoicesPtr *sPtr, int row, int column)
{
  ChoicesPtr newPtr = malloc(sizeof(Choices));//allocate memory

  newPtr->choice.row = row;
  newPtr->choice.col = column;

  ChoicesPtr previousPtr = NULL;  //pointer to previous node in list
  ChoicesPtr currentPtr = *sPtr; //pointer to current node in list

  //loop to find the correct location in the list
  while (currentPtr != NULL && row > currentPtr->choice.row)
  {
    previousPtr = currentPtr; //walk to ...
    currentPtr = currentPtr->next; //... next node
  }

  //insert new node at beginning of list
  if (previousPtr == NULL)
  {
    newPtr->next = *sPtr;
    *sPtr = newPtr;
  }
  else //insert new node between previousPtr and currentPtr
  {
    previousPtr->next = newPtr;
    newPtr->next =currentPtr;
  }
}

//display possible moves onto terminal
void printMoves(ChoicesPtr currentPtr, player *player1, player *player2, char name[20])
{
  if (currentPtr == NULL) //if there are no elements in linked list:
  {
    printf("NO POSSIBLE MOVES!  END OF GAME.\n");
    finalResult(player1, player2); //display final result
  }
  else //if there are elements in list, display moves on terminal
  {
    printf("\n%s, choose your next move (row, col):\n", name);

    int i = 1;
    //while loop to print out all possible moves
    while (currentPtr != NULL)
    {
      printf("%d.(%d, %d)\t", i, currentPtr->choice.row+1, currentPtr->choice.col+1);
      currentPtr = currentPtr->next;
      i++;
    }
    printf("\n? ");
  }
}

//remove duplicates moves from the linked list
void removeDup(ChoicesPtr *sPtr)
{
  ChoicesPtr currentPtr, nextPtr, duplicate;

  currentPtr = *sPtr;

  //compare each element with the rest of the elements
  while (currentPtr != NULL && currentPtr->next != NULL)
  {
    nextPtr = currentPtr;

    while (nextPtr->next != NULL)
    {
      //if there is a duplicate delete it
      if ((currentPtr->choice.row == nextPtr->next->choice.row) && (currentPtr->choice.col == nextPtr->next->choice.col))
      {
        duplicate = nextPtr->next;
        nextPtr->next = nextPtr->next->next;
        free(duplicate);
      }
      else
      {
        nextPtr = nextPtr->next;
      }
    }
    currentPtr = currentPtr->next;
  }
}

//implement the following to the changeColour function
//this deletes all elements in linked list for following set of moves
ChoicesPtr temp;

while (startPtr != NULL)
{
  temp = startPtr;
  startPtr = temp->next;
  free(temp);
}
