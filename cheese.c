#include "defs.h"

int main(void) {
    allInit();
    S_BOARD board[1];
    S_MOVELIST list[1];

    parseFen(START_FEN, board);
    generateAllMoves(board, list);

    printMoveList(list);

    int moveNum = 0;
    int move = 0;

    printBoard(board);

    getchar();

    for(moveNum = 0; moveNum < list->count; ++moveNum){
        move = list->moves[moveNum].move;

        if(!makeMove(board, move)){
            continue;
        }

        printf("\nMADE: %s\n", ptMove(move));
        printBoard(board);

        takeMove(board);
        printf("\nTAKEN: %s\n", ptMove(move));
        printBoard(board);

        getchar();
    }

    return EXIT_SUCCESS;
}
