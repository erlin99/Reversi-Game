#ifndef DISKSANDPLAYERS_H_
#define DISKSANDPLAYERS_H_

#define SIZE 8

enum colour {
  WHITE,
  BLACK,
  NONE
};

typedef struct position {
  int row;
  int col;
} position;

typedef struct disk {
  enum colour type;
  position pos;
} disk;

typedef struct player {
  char name[20];
  enum colour type;
  int points;
} player;

//struct for linked list to store possible user's choices
typedef struct choices {
  struct position choice;
  struct choices *next;
} Choices;

typedef Choices *ChoicesPtr;

void initializePlayers(player *player1, player *player2);

void initializeBoard(disk board[SIZE][SIZE], player player1, player player2);

void printBoard(disk board[SIZE][SIZE]);

void playGame(player *player1, player *player2, disk board[SIZE][SIZE]);

void finalResult(player *player1, player *player2);

void insertMoves(ChoicesPtr *sPtr, int row, int column);

void printMoves(ChoicesPtr currentPtr, player *player1, player *player2, char name[20]);

void checkMoves(disk board[SIZE][SIZE], ChoicesPtr *startPtr);

#endif
