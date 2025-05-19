#include "defs.h"

char* ptSq(const int sq){
    static char sqStr[3];

    int file = filesBrd[sq];
    int rank = ranksBrd[sq];

    sprintf(sqStr, "%c%c", ('a'+file), ('1'+rank));

    return sqStr;
}

char* ptMove(const int move){
    static char mvStr[6];

    int ff = filesBrd[FROMSQ(move)];
    int rf = ranksBrd[FROMSQ(move)];
    int ft = filesBrd[TOSQ(move)];
    int rt = ranksBrd[TOSQ(move)];

    int promoted = PROMOTED(move);

    if(promoted){
        char pchar = 'q';
        if(isKn(promoted)){
            pchar = 'n';
        } else if(isRQ(promoted) && !isBQ(promoted)){
            pchar = 'r';
        } else if(isBQ(promoted) && !isRQ(promoted)){
            pchar = 'b';
        }
        sprintf(mvStr, "%c%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt), pchar);
    }
    else{
        sprintf(mvStr, "%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt));
    }

    return mvStr;
}

void printMoveList(const S_MOVELIST* list){
    int index = 0;
    int score = 0;
    int move = 0;
    printf("Movelist:\n");

    for(index = 0; index < list->count; ++index){
        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move: %d > %s (score: %d)\n", index+1, ptMove(move), score);
    }
    printf("MoveList Total %d moves\n\n", list->count);
}