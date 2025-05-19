#include "defs.h"

#define PAWNMOVESW "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"

int main(void) {
    allInit();
    S_BOARD board[1];

    parseFen(PAWNMOVESW, board);
    printBoard(board);

    S_MOVELIST list[1];

    generateAllMoves(board, list);

    printMoveList(list);

    return EXIT_SUCCESS;
}
