#include "gameController.h"

Game game;

void newGame() {
    Board board;
    board.total = 0;

    History history;
    history.total = 0;

    Heap heap;
    heap.total = 0;

    game.history = history;
    game.board = board;
    game.heap = heap;


    fill(&game);

    setPlayers(&game);

    draw(&game, 0, 7);
    draw(&game, 1, 7);


    startGame(&game);
}

void continueGame()
{
    game = loadLastGame();
    startGame(&game);
}
