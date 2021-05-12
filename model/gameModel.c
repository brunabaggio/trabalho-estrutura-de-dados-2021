
#include "gameView.h"
#include <string.h>

void fill(Game *game)
{
    int counter = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            Piece piece = {i, j};
            game->heap.pieces[counter] = piece;
            counter++;
            game->heap.total = counter;
        }
    }
}

void setPlayers(Game *game)
{
    int choice = 0;
    do {
        choice = setPlayersMenu();
    } while (choice != 1 && choice != 2);

    for (int i = 0; i < choice; ++i) {
        Player player = newPlayer();
        game->players[i] = player;
        game->players[i].cpu = false;
    }

    if (choice == 1) {
        Player cpu;
        cpu.cpu = true;
        game->players[1] = cpu;
    }
}

void cpu(Game *game)
{
    bool turnHasEnded = false;
    bool drewOnce = false;
    int boardTotal = game->board.total;
    Piece firstPiece = game->board.pieces[0];
    Piece lastPiece = game->board.pieces[boardTotal - 1];
    Piece currentPiece;
    int chosen = -1;
    int option = 2;

    do {
        for (int x = 0; x < game->players[1].total; x++) {
            currentPiece = game->players[1].hand[x];

            if (firstPiece.SideA == currentPiece.SideA  || firstPiece.SideA == currentPiece.SideB) {
                chosen = x;
                option = 1;
                break;
            }

            if (lastPiece.SideB == currentPiece.SideA || lastPiece.SideB == currentPiece.SideB) {
                chosen = x;
                option = 1;
                break;
            }
        }

        if (option == 2 && drewOnce == true) {
            option = 3;
        }

        switch (option) {
            case 1:
                turn(game, 1, chosen);
                turnHasEnded = true;
                break;
            case 2:
                draw(game, 1, 1);
                drewOnce = true;
                break;
            case 3:
                turnHasEnded = true;
                break;
        }
    } while (turnHasEnded == false);
}

void draw(Game *game, int player, int total)
{
    int access;

    for (int i = 0; i < total; i++) {
        srand(time(NULL) * rand());
        do {
            access = rand() % 27;
        } while (isPieceUsed(game, access) == true);

        Piece p = game->heap.pieces[access];

        int playerTotalInHand = game->players[player].total;
        game->players[player].hand[playerTotalInHand] = p;
        game->players[player].total += 1;

        game->history.used[game->history.total] = access;
        game->history.total += 1;
    }
}

bool isPieceUsed(Game *game, int position)
{
    for (int i = 0; i < game->history.total; i++) {
        if (game->history.used[i] == position) {
            return true;
        }
    }

    return false;
}

int firstPlayer(Game *game)
{
    int playerGreaterPiece[2], firstPlayerPoints, secondPlayerPoints;

    for (int p = 0; p < 2; p++) {
        playerGreaterPiece[p] = getGreaterEqualPiece(game, p);
    }

    if (playerGreaterPiece[0] == -1 && playerGreaterPiece[1] == -1) {
        for (int p = 0; p < 2; p++) {
            playerGreaterPiece[p] = getGreaterPiece(game, p);
        }

        firstPlayerPoints = game->players[0].hand[playerGreaterPiece[0]].SideA + game->players[0].hand[playerGreaterPiece[0]].SideB;
        secondPlayerPoints = game->players[1].hand[playerGreaterPiece[1]].SideA + game->players[1].hand[playerGreaterPiece[1]].SideB;

        if (firstPlayerPoints >= secondPlayerPoints) {
            turn(game, 0, playerGreaterPiece[0]);
            return 0;
        }

        turn(game, 1, playerGreaterPiece[1]);
        return 1;
    }

    if (playerGreaterPiece[0] > -1 && playerGreaterPiece[1] > -1) {
        firstPlayerPoints = game->players[0].hand[playerGreaterPiece[0]].SideA + game->players[0].hand[playerGreaterPiece[0]].SideB;
        secondPlayerPoints = game->players[1].hand[playerGreaterPiece[1]].SideA + game->players[1].hand[playerGreaterPiece[1]].SideB;

        if (firstPlayerPoints >= secondPlayerPoints) {
            turn(game, 0, playerGreaterPiece[0]);
            return 0;
        }

        turn(game, 1, playerGreaterPiece[1]);
        return 1;
    }

    if (playerGreaterPiece[0] > -1) {
        turn(game, 0, playerGreaterPiece[0]);
        return 0;
    }

    if (playerGreaterPiece[1] > -1) {
        turn(game, 1, playerGreaterPiece[1]);
        return 1;
    }

    return 0;
}

void startGame(Game *game)
{
    bool endGame = false;
    int turn = firstPlayer(game);

    do {
        if (turn == 0) {
            turn = 1;
        } else {
            turn = 0;
        }

        endGame = play(game, turn);
    } while (endGame != true);
}

void turn(Game *game, int player, int handPosition)
{
    if (handPosition == -1) {
        handPosition = chooseAPiece(game, player);
    }

    for (int x = 0; x < game->players[player].total; x++) {
        if (x == handPosition) {
            Piece piece = game->players[player].hand[handPosition];
            printf("\n");

            if (game->board.total == 0) {
                int total = game->board.total;
                game->board.pieces[total] = piece;
                game->board.total ++;

                movePlayerHand(game, player, handPosition);
                game->players[player].total--;

                break;
            }

            Piece firstPieceFromBoard = game->board.pieces[0];
            Piece lastPieceFromBoard = game->board.pieces[game->board.total-1];

            if (!isChosenPieceValid(piece, firstPieceFromBoard, lastPieceFromBoard)) {
                alert("Esta peca nao cabe na mesa. Voce perdeu a vez.\n");
                return;
            }

            switchSides(&piece, firstPieceFromBoard, lastPieceFromBoard);

            movePlayerHand(game, player, handPosition);
            game->players[player].total--;

            if (piece.SideB == firstPieceFromBoard.SideA) {
                moveBoardPieces(game, 0);
                game->board.pieces[0] = piece;
                game->board.total ++;
            } else if(piece.SideA == lastPieceFromBoard.SideB) {
                int total = game->board.total;
                game->board.pieces[total] = piece;
                game->board.total ++;
            }
        }
    }
}

void movePlayerHand(Game *game, int player, int from)
{
    int total = game->players[player].total;

    for (int i = from; i < total - 1; i++) {
        game->players[player].hand[i] = game->players[player].hand[i + 1];
    }
}

void moveBoardPieces(Game *game, int from)
{
    for (int i = game->board.total - 1; i >= from; i--) {
        game->board.pieces[i + 1] = game->board.pieces[i];
    }
}

bool play(Game *game, int playerTurn)
{
    int option;
    bool drewOnce = false;
    bool turnHasFinished = false;

    displayTable(game);
    displayPlayersHand(game, playerTurn, true);

    do {
        if (playerTurn == 1 && game->players[1].cpu == true) {
            cpu(game);
            break;
        }
        option = showGameMenu();

        switch (option) {
            case 1:
                turn(game, playerTurn, -1);
                turnHasFinished = true;
                break;
            case 2:
                draw(game, playerTurn, 1);
                displayPlayersHand(game, playerTurn, false);
                drewOnce = true;
                break;
            case 3:
                turnHasFinished = true;

                if (drewOnce == false) {
                    alert("Voce precisa jogar ou comprar uma peca. Tente novamente\n");
                    turnHasFinished = false;
                }
                break;
            case 4:
                saveGame(game);
                printf("Jogo salvo! Encerrando.");
                exit(0);
                break;
            case 0:
                alert("Voce desistiu do jogo.\n");
                if (playerTurn == 0) {
                    playerTurn = 1;
                } else {
                    playerTurn = 0;
                }
                game->players[playerTurn].total = 0;
                turnHasFinished = true;
                break;
            default:
                alert("Peca invalida!\n");
                break;
        }
    } while (turnHasFinished == false);

    return isGameEnded(game, playerTurn);
}

bool isGameEnded(Game *game, int turn)
{
    if (game->players[turn].total == 0) {
        showWinner(game, turn);
        return true;
    }

    return false;
}

bool isChosenPieceValid(Piece chosenPiece, Piece firstPiece, Piece lastPiece)
{
    if ((chosenPiece.SideA == firstPiece.SideA) || (chosenPiece.SideB == firstPiece.SideA)) {
        return true;
    }

    if ((chosenPiece.SideA == lastPiece.SideB) || (chosenPiece.SideB == lastPiece.SideB)) {
        return true;
    }

    return false;
}

void switchSides(Piece *chosenPiece, Piece firstPiece, Piece lastPiece)
{
    int swap;
    if (chosenPiece->SideA == firstPiece.SideA) {
        swap = chosenPiece->SideB;
        chosenPiece->SideB = chosenPiece->SideA;
        chosenPiece->SideA = swap;

        return;
    }

    if (chosenPiece->SideB == lastPiece.SideB) {
        swap = chosenPiece->SideA;
        chosenPiece->SideA = chosenPiece->SideB;
        chosenPiece->SideB = swap;
    }
}

Game loadLastGame()
{
    Game game;
    FILE * file;

    file = fopen("../saves/save.bin", "rb");

    if (file == NULL) {
        return game;
    }

    fread(&game, sizeof(game), 1, file);

    return  game;
}

void saveGame(Game * game)
{
    FILE * file;
    file = fopen("../saves/save.bin", "wb");

    fwrite(game, sizeof(*game), 1, file);
}

int getGreaterEqualPiece(Game *game, int playerTurn)
{
    int sum, higher, piecePosition;

    sum = 0;
    higher = 0;
    piecePosition = -1;

    for (int i = 0; i < game->players[playerTurn].total; i++) {
        if (game->players[playerTurn].hand[i].SideA == game->players[playerTurn].hand[i].SideB) {
            sum = game->players[playerTurn].hand[i].SideA + game->players[playerTurn].hand[i].SideB;

            if (sum >= higher) {
                higher = sum;
                piecePosition = i;
            }
        }
    }

    return piecePosition;
}

int getGreaterPiece(Game *game, int playerTurn)
{
    int sum, higher, piecePosition;

    sum = 0;
    higher = 0;
    piecePosition = -1;

    for (int i = 0; i < game->players[playerTurn].total; i ++) {
        sum = game->players[playerTurn].hand[i].SideA + game->players[playerTurn].hand[i].SideB;

        if (sum > higher) {
            higher = sum;
            piecePosition = i;
        }
    }

    return piecePosition;
}
