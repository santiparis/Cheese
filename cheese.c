#include "defs.h"

#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"
#define CASTLE2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main(void) {
    allInit();
    S_BOARD board[1];
    S_MOVELIST list[1];

    parseFen(CASTLE2, board);
    generateAllMoves(board, list);

    printMoveList(list);

    return EXIT_SUCCESS;
}
