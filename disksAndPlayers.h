/*COMP10050		Assignment 3	 Written by: Er Lin & Dylan Garrett
Dylan Garrett - 17375763
Er Lin - 17328173
Program that simulates the Othello/Reversi Game*/

#ifndef DISKSANDPLAYERS_H_
#define DISKSANDPLAYERS_H_

#define SIZE 8

enum colour {
  WHITE,
  BLACK,
  NONE
};

//struct for position on board
typedef struct position {
  int row;
  int col;
} position;

//struct for each disk type and position
typedef struct disk {
  enum colour type;
  position pos;
} disk;

//struct to store user's information
typedef struct player {
  char name[20];
  enum colour type;
  int points;
} player;

//struct for linked list to store possible user's moves
typedef struct choices {
  struct position choice;
  struct choices *next;
} Choices;

typedef Choices *ChoicesPtr;

//initialize players with names and points
void initializePlayers(player *player1, player *player2);

//initiliaze board with the starting positions
void initializeBoard(disk board[SIZE][SIZE], player player1, player player2);

//print current status of board and points
void printBoardAndPoints(disk board[SIZE][SIZE], player *player1, player *player2);

//game logic
void playGame(player *player1, player *player2, disk board[SIZE][SIZE]);

//display final result on terminal and to text file
void finalResult(player *player1, player *player2);

//insert possible moves into a linked list
void insertMoves(ChoicesPtr *sPtr, int row, int column);

//display on terminal the possible moves stored in linked list
void printMoves(ChoicesPtr currentPtr, char name[20]);

//check possible moves at each turn
int checkMoves(disk board[SIZE][SIZE], ChoicesPtr *startPtr, int TYPE);

//check for duplicated possible moves and delete
void removeDup(ChoicesPtr *sPtr);

//change the colours of other disks once a move is made
void colourChange(int x, int y, disk board[SIZE][SIZE], player *playerMoving);

#endif
