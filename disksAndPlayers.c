/*COMP10050		Assignment 3	 Written by: Er Lin & Dylan Garrett
Dylan Garrett - 17375763
Er Lin - 17328173
Program that simulates the Othello/Reversi Game*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "disksAndPlayers.h"

//initialize players with names and points
void initializePlayers(player *player1, player *player2)
{
  int nameSize;
  int colorChoice;

  //ask player one for the name and replace \n with \0 and convert first letter to capital letter
  printf("What is the name of player one?\n");
  fgets(player1->name, 20, stdin);
  nameSize = strlen(player1->name);
  player1->name[nameSize -1] = '\0';
  player1->name[0] = toupper(player1->name[0]);

  //ask player two for the name and replace \n with \0 and convert first letter to capital letter
  printf("What is the name of player two?\n");
  fgets(player2->name, 20, stdin);
  nameSize = strlen(player2->name);
  player2->name[nameSize - 1] = '\0';
  player2->name[0] = toupper(player2->name[0]);

  //ask first player to choose a colour
  do {
    printf("%s, what colour would you like to be?(WHITE = 0, BLACk = 1)\n", player1->name);
    scanf("%d", &colorChoice);
  } while(colorChoice != 0 && colorChoice != 1);

  //assign colours to players depending on the choice
  if (colorChoice == 1)
  {
    player1->type = BLACK;
    player2->type = WHITE;

    printf("\n%s --> BLACK (@)\n", player1->name);
    printf("%s --> WHITE (O)\n", player2->name);
  }
  else
  {
    player1->type = WHITE;
    player2->type = BLACK;

    printf("\n%s --> WHITE (@)\n", player1->name);
    printf("%s --> BLACK (O)\n", player2->name);
  }
}

//initiliaze board with the starting positions
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

//print current status of board and points
void printBoardAndPoints(disk board[SIZE][SIZE], player *player1, player *player2)
{
  int i, j;
  //initiliaze pointers for the 2 disk types
  player *blackPlayer;
  player *whitePlayer;
  //assign pointers depending on each player's disk type
  if (player1->type == BLACK) {
    blackPlayer = player1;
    whitePlayer = player2;
  }
  else {
    blackPlayer = player2;
    whitePlayer = player1;
  }

  blackPlayer -> points = 0;
  whitePlayer -> points = 0;

  printf("\n    ");

  for(i = 0; i < SIZE; i++)
  {
    printf("%d   ",i+1);//print numbers on the x axis
  }
  for(i = 0; i < SIZE; i++)
  {
    printf("\n%d | ", i+1); //print numbers on the y axis

    for(j=0;j<SIZE; j++) //depending on the type of the cell print @, O or x
    {
      switch(board[i][j].type)
      {
        case BLACK:
          printf("@ | ");
          blackPlayer -> points++;
          break;
        case WHITE:
          printf("O | ");
          whitePlayer -> points++;
          break;
        case NONE:
          printf("x | ");
          break;
        default:
          break;
      }
    }
  }
  //display points from each player
  printf("\n\n%s --> %d points.\n", player1->name, player1->points);
  printf("%s --> %d points.", player2->name, player2->points);
}

//game logic
void playGame(player *player1, player *player2, disk board[SIZE][SIZE])
{
  ChoicesPtr startPtr = NULL; //pointer to keep track of linked list
  ChoicesPtr temp;
  int choice, i, r, c, count;

  //initiliaze pointers for the 2 disk types
  player *blackPlayer;
  player *whitePlayer;
  //assign pointers depending on each player's disk type
  if (player1->type == BLACK) {
    blackPlayer = player1;
    whitePlayer = player2;
  }
  else {
    blackPlayer = player2;
    whitePlayer = player1;
  }

  //while there is still space on the board
  while (player1->points + player2->points != 64)
  {
    //player with black disks moves
    count = checkMoves(board, &startPtr, blackPlayer->type);
    //if there are no more possible moves, end game
    if (count == 0) {
      printf("\nNO MORE POSSIBLE MOVES!  END OF GAME.\n");
      break;
    }
    else {
      removeDup(&startPtr);
      printMoves(startPtr, blackPlayer->name);
      printf("\n?  ");
      scanf("%d", &choice); //scan user's choice
      //while loop to make sure of valid input from user
      while (choice > count || choice <= 0) {
        printf("Please enter a valid INPUT\n");
        printf("? ");
        scanf("%d", &choice);
      }
      //find choice in the linked list and extract values for row and column
      for (i = 0; i < choice; i++)
      {
        r = startPtr->choice.row;
        c = startPtr->choice.col;
        startPtr = startPtr->next;
      }
      colourChange(r, c, board, blackPlayer);
      printBoardAndPoints(board, player1, player2);
      //delete all elements in linked list (free the space)
      while (startPtr != NULL)
      {
        temp = startPtr;
        startPtr = temp->next;
        free(temp);
      }
    }
    //player with white disks moves
    count = checkMoves(board, &startPtr, whitePlayer->type);
    //if no more possbile moves, end game
    if (count == 0) {
      printf("\nNO MORE POSSIBLE MOVES!  END OF GAME.\n");
      break;
    }
    else {
      removeDup(&startPtr);
      printMoves(startPtr, whitePlayer->name);
      printf("\n?  ");
      scanf("%d", &choice); //scan user's choice
      //while loop to make sure of valid input from user
      while (choice > count || choice <= 0) {
        printf("Please enter a valid INPUT\n");
        printf("? ");
        scanf("%d", &choice);
      }
      //find choice in the linked list and extract values for row and column
      for (i = 0; i < choice; i++)
      {
        r = startPtr->choice.row;
        c = startPtr->choice.col;
        startPtr = startPtr->next;
      }
      colourChange(r, c, board, whitePlayer);
      printBoardAndPoints(board, player1, player2);
      //delete all elements in linked list (free the space)
      while (startPtr != NULL)
      {
        temp = startPtr;
        startPtr = temp->next;
        free(temp);
      }
    }
  }
}

//display final result on terminal and to text file
void finalResult(player *player1, player *player2)
{
  FILE *filePtr;//pointer to rext file

  //print results to terminal
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

  //if file cannot be created, print warning message
  if ((filePtr = fopen("result.txt", "w")) == NULL)
  {
    printf("Text file to store result couldn't be created.\n");
  }
  else//if file is succesfully created, enter results into the file
  {
    fprintf(filePtr, "Player 1: %s. Points: %d.\n", player1->name, player1->points);

    fprintf(filePtr, "Player 2: %s. Points: %d.\n", player2->name, player2->points);

    //if player 1 has more points
    if (player1->points > player2->points) {
      fprintf(filePtr, "\nThe WINNER is: %s\n", player1->name);
    }
    //if player 2 has more points
    else if (player2->points > player1->points) {
      fprintf(filePtr, "\nThe WINNER is: %s\n", player2->name);
    }
    //in the case of a tie
    else {
      fprintf(filePtr, "\nIt's a DRAW\n");
    }
  }

  fclose(filePtr); //close file
}

//compute possible moves and insert them to linked list
int checkMoves(disk board[SIZE][SIZE], ChoicesPtr *startPtr, int TYPE)
{
  int TYPE2;
  int count = 0;
  //assign variables depending on the player moving
  if (TYPE == BLACK) {
    TYPE2 = WHITE;
  }
  else {
    TYPE2 = BLACK;
  }

  int i, j, k, l;
  for(i = 0; i < SIZE; i++) //control rows
  {
    for(j = 0; j < SIZE; j++) //control columns
    {
      //checks the board for moving player disks
      if(board[i][j].type ==  TYPE)
      {
        //checking for possible moves to the RIGHT
        if(board[i][j+1].type == TYPE2)
        {
          l = j+1;
          while (l < SIZE && board[i][l].type != TYPE) {
            if (board[i][l].type == NONE) {
              insertMoves(startPtr, i, l);
              count++;
              break;
            }
            l++;
          }
        }
        //checking for possible moves to the LEFT
        if(board[i][j-1].type == TYPE2)
        {
          l = j-1;
          while (l >= 0 && board[i][l].type != TYPE) {
            if (board[i][l].type == NONE) {
              insertMoves(startPtr, i, l);
              count++;
              break;
            }
            l--;
          }
        }
        //checking possible moves DOWNWARDS
        if(board[i+1][j].type == TYPE2)
        {
          k = i+1;
          while (k < SIZE && board[k][j].type != TYPE) {
            if (board[k][j].type == NONE) {
              insertMoves(startPtr, k, j);
              count++;
              break;
            }
            k++;
          }
        }
        //checking possible moves UPWARDS
        if(board[i-1][j].type == TYPE2)
        {
          k = i-1;
          while (k >= 0 && board[k][j].type != TYPE) {
            if (board[k][j].type == NONE) {
              insertMoves(startPtr, k, j);
              count++;
              break;
            }
            k--;
          }
        }
        //checking possible moves RIGHT-DOWN DIAGONAL
        if(board[i+1][j+1].type == TYPE2)
        {
          k = i+1;
          l = j+1;
          while (k < SIZE && l < SIZE && board[k][l].type != TYPE) {
            if (board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              count++;
              break;
            }
            k++;
            l++;
          }
        }
        //checking possible moves LEFT-DOWN DIAGONAL
        if(board[i+1][j-1].type == TYPE2)
        {
          k = i+1;
          l = j-1;
          while (k < SIZE && l >= 0 && board[k][l].type != TYPE) {
            if (board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              count++;
              break;
            }
            k++;
            l--;
          }
        }
        //checking possible moves RIGHT-UP DIAGONAL
        if(board[i-1][j+1].type == TYPE2)
        {
          k = i-1;
          l = j+1;
          while (k >= 0 && l < SIZE && board[k][l].type != TYPE) {
            if (board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              count++;
              break;
            }
            k--;
            l++;
          }
        }
        //checking possible moves LEFT-UP DIAGONAL
        if(board[i-1][j-1].type == TYPE2)
        {
          k = i-1;
          l = j-1;
          while (k >= 0 && l >= 0 && board[k][l].type != TYPE) {
            if (board[k][l].type == NONE) {
              insertMoves(startPtr, k, l);
              count++;
              break;
            }
            k--;
            l--;
          }
        }
      }
    }
  }
  return count;
}

//change the colours of other disks once a move is made
void colourChange(int x, int y, disk board[SIZE][SIZE], player *playerMoving)
{
  int TYPE = playerMoving->type;
  int TYPE2;
  //assign variables depending on player moving
  if (TYPE == BLACK) {
    TYPE2 = WHITE;
  }
  else {
    TYPE2 = BLACK;
  }

  board[x][y].type = TYPE;//change colour of selected position

  int i, j, k, l;
  //change colours going RIGHT
  if(board[x][y+1].type == TYPE2)
  {
    for (j = y+1; j < SIZE; j++)
    {
      //if there a closing disk on other side:
      if (board[x][j].type == TYPE) {
        l = y+1;
        while(board[x][l].type != TYPE && l < SIZE)
        {
          board[x][l].type = TYPE; //replace disks
          l++;
        }
        break;
      }
    }
  }
  //change colours going LEFT
  if(board[x][y-1].type == TYPE2)
  {
    for (j = y-1; j >= 0; j--)
    {
      //if there a closing disk on other side:
      if (board[x][j].type == TYPE)
      {
        l = y-1;
        while(board[x][l].type != TYPE && l >= 0)
        {
          board[x][l].type = TYPE;//replace disks
          l--;
        }
        break;
      }
    }
  }
  //change colours DOWNWARDS
  if(board[x+1][y].type == TYPE2)
  {
    for (i = x+1; i < SIZE; i++)
    {
      //if there a closing disk on other side:
      if (board[i][y].type == TYPE)
      {
        k = x+1;
        while(board[k][y].type != TYPE && l < SIZE)
        {
          board[k][y].type = TYPE;//replace disks
          k++;
        }
        break;
      }
    }
  }
  //change colour UPWARDS
  if(board[x-1][y].type == TYPE2)
  {
    for (i = x-1; i >= 0; i--)
    {
      //if there a closing disk on other side:
      if (board[i][y].type == TYPE)
      {
        k = x-1;
        while(board[k][y].type != TYPE &&  k >= 0)
        {
          board[k][y].type = TYPE;//replace disks
          k--;
        }
        break;
      }
    }
  }
  //change colour RIGHT-DOWN DIAGONAL
  if(board[x+1][y+1].type == TYPE2)
  {
    for (i = x+1, j = y+1; i < SIZE && j < SIZE; i++, j++)
    {
      //if there a closing disk on other side:
      if (board[i][j].type == TYPE)
      {
        k = x+1;
        l = y+1;
        while(board[k][l].type != TYPE && k < SIZE && l < SIZE)
        {
          board[k][l].type = TYPE;//replace disks
          k++;
          l++;
        }
        break;
      }
    }
  }
  //change colour RIGHT-UP DIAGONAL
  if(board[x-1][y+1].type == TYPE2)
  {
    for (i = x-1, j = y+1; i >= 0 && j < SIZE; i--, j++)
    {
      //if there a closing disk on other side:
      if (board[i][j].type == TYPE)
      {
        k = x-1;
        l = y+1;
        while(board[k][l].type != TYPE && k >= 0 && l < SIZE)
        {
          board[k][l].type = TYPE;//replace disks
          k--;
          l++;
        }
        break;
      }
    }
  }
  //change colour LEFT-DOWN DIAGONAL
  if(board[x+1][y-1].type == TYPE2)
  {
    for (i = x+1, j = y-1; i < SIZE && j >= 0; i++, j--)
    {
      //if there a closing disk on other side:
      if (board[i][j].type == TYPE)
      {
        k = x+1;
        l = y-1;
        while(board[k][l].type != TYPE && k < SIZE && l >= 0)
        {
          board[k][l].type = TYPE;//replace disks
          k++;
          l--;
        }
        break;
      }
    }
  }
  //change colour LEFT-UP DIAGONAL
  if(board[x-1][y-1].type == TYPE2)
  {
    for (i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--)
    {
      //if there a closing disk on other side:
      if (board[i][j].type == TYPE)
      {
        k = x-1;
        l = y-1;
        while(board[k][l].type != TYPE && k >= 0 && l >= 0)
        {
          board[k][l].type = TYPE;//replace disks
          k--;
          l--;
        }
        break;
      }
    }
  }
}

//insert possible moves into a linked list
void insertMoves(ChoicesPtr *sPtr, int row, int column)
{
  ChoicesPtr newPtr = malloc(sizeof(Choices));//allocate memory

  //enter values into the new node
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

//display on terminal the possible moves stored in linked list
void printMoves(ChoicesPtr currentPtr, char name[20])
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
}

//check for duplicated possible moves and delete
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
      else //if there is no duplicate move onto next
      {
        nextPtr = nextPtr->next;
      }
    }
    currentPtr = currentPtr->next;
  }
}
