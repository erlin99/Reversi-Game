#ifndef DISKSANDPLAYERS_H_
#define DISKSANDPLAYERS_H_

#define SIZE 8

enum colour {
  WHITE,
  BLACK,
  NONE
};

//struct for linked list to store the possible choices
typedef struct choices {
  position choice;
  struct choices *next;
} choices;

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

void initializePlayers(player *player1, player *player2);

void initializeBoard(disk board[SIZE][SIZE], player player1, player player2);

void printBoard(disk board[SIZE][SIZE]);

void playGame(player *player1, player *player2, disk board[SIZE][SIZE]);

void finalResult(player *player1, player *player2);

#endif
