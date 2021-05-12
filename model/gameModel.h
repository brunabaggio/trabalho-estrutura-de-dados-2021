
#include <stdbool.h>

#ifndef DOMINO_GAMEMODEL_H
#define DOMINO_GAMEMODEL_H

#endif 

typedef struct Piece {
    int SideA;
    int SideB;
} Piece;

typedef struct Player {
    char nickname[50];
    Piece hand[21];
    int total;
    bool cpu;
} Player;

typedef struct Heap {
    Piece pieces[28];
    int total;
} Heap;

typedef struct History {
    int total;
    int used[28];
} History;

typedef struct Board {
    int total;
    Piece pieces[28];
} Board;

typedef struct Game {
    Board board;
    Heap heap;
    History history;
    Player players[2];
} Game;

int firstPlayer(Game *game);

void fill(Game *game);

void setPlayers(Game *game);

void draw(Game *game, int player, int total);

bool isPieceUsed(Game *game, int position);

bool play(Game *game, int turn);

void startGame(Game *game);

void turn(Game *game, int player, int handPosition);

void movePlayerHand(Game *game, int player, int from);

void moveBoardPieces(Game *game, int from);

bool isGameEnded(Game *game, int turn);

bool isChosenPieceValid(Piece chosenPiece, Piece firstPiece, Piece lastPiece);

void switchSides(Piece *chosenPiece, Piece firstPiece, Piece lastPiece);

Game loadLastGame();

void saveGame(Game * game);

int getGreaterEqualPiece(Game *game, int playerTurn);

int getGreaterPiece(Game *game, int playerTurn);

void cpu(Game *game);
