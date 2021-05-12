#ifndef DOMINO_GAMEVIEW_H
#define DOMINO_GAMEVIEW_H

#endif

#include<time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "gameModel.h"

void alert(char message[]);

Player newPlayer();

void start(Game *game);

void display(Piece p);

void displayTable(Game *game);

int showGameMenu();

void displayPlayersHand(Game *game, int turn, bool showPlayerTurnMessage);

int chooseAPiece(Game *game, int playerTurn);

int showMainMenu();

void showRules();

int setPlayersMenu();

void showWinner(Game *game, int turn);
