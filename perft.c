#include "defs.h"

long leafNodes;

void perft(const int depth, S_BOARD* pos){
    ASSERT(checkBoard(pos));

    if(depth == 0){
        leafNodes++;
        return;
    }

    S_MOVELIST list[1];
    generateAllMoves(pos, list);

    int moveNum = 0;
    for(moveNum = 0; moveNum < list->count; ++moveNum){
        if(!makeMove(pos, list->moves[moveNum].move)){
            continue;
        }
        perft(depth - 1, pos);
        takeMove(pos);
    }
    return;
}

void perftTest(int depth, S_BOARD* pos){
    ASSERT(checkBoard(pos));

    printBoard(pos);

    printf("\nStarting Test to Depth: %d\n", depth);

    leafNodes = 0;

    S_MOVELIST list[1];
    generateAllMoves(pos, list);

    int move;
    int moveNum = 0;
    for(moveNum = 0; moveNum < list->count; ++moveNum){
        move = list->moves[moveNum].move;
        if(!makeMove(pos, move)){
            continue;
        }
        long cumNodes = leafNodes;
        perft(depth - 1, pos);
        takeMove(pos);
        long oldnodes = leafNodes - cumNodes;
        printf("Move %d: %s : %ld\n", moveNum+1, ptMove(move), oldnodes);
    }
    printf("\nTest Complete: %ld node visited\n", leafNodes);
    return;
}