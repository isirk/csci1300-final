// ...existing code...
#include "files/Board.h"
#include <cstdlib> // for srand()
#include <ctime>
#include <iostream>

int main() {
    // seed random so initializeTiles produces varied boards
    std::srand((unsigned)std::time(nullptr));

    // create and initialize board (constructor calls initializeBoard)
    Board board;

    // show initial board
    board.displayBoard();

    // example: move player 0 twice and show board after each move
    for (int i = 0; i < 2; ++i) {
        bool finished = board.movePlayer(0); // move player at lane 0 forward one tile
        std::cout << "\nAfter move " << (i + 1) << " (player 1):\n";
        board.displayBoard();
        if (finished) {
            std::cout << "Player 1 reached the finish!\n";
            break;
        }
    }

    return 0;
}