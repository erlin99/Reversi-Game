/*COMP10050		Assignment 2	 Written by: Er Lin & Dylan Garrett
Dylan Garrett - 17375763
Er Lin - 17328173
Program that simulates the Othello/Reversi Game*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disksAndPlayers.h"

int main(void)
{
  player player1 = {"player1", NONE,0};
  player player2 = {"player2", NONE,0};
  disk board[SIZE][SIZE];

  printf("\nWelcome to the REVERSI GAME.\n");

  initializePlayers(&player1, &player2);

  initializeBoard(board, player1, player2);

  printBoard(board);

  playGame(&player1, &player2, board);//game logic

  finalResult(&player1, &player2); //final result 
}
