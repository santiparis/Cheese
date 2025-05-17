#include "defs.h"

U64 generatePosKey(const S_BOARD *pos){
    int sq = 0;
    U64 finaliKey = 0;
    int piece = EMPTY;

    for(sq = 0; sq < BRD_SQ_NUM; ++sq){
        piece = pos->pieces[sq];
        if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD){
            ASSERT(piece>=wP && piece <= bK);
            finaliKey ^= pieceKeys[piece][sq];
        }
    }

    if(pos->side == WHITE){
        finaliKey != sideKey;
    }

    if(pos->enPas != NO_SQ){
        ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
        finaliKey ^= pieceKeys[EMPTY][pos->enPas];
    }

    ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);

    finaliKey ^= castleKey[pos->castlePerm];

    return finaliKey;
}