#include "defs.h"

const int knDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int rkDir[4] = {-1, -10, 1, 10};
const int biDir[4] = {-9, -11, 11, 9};
const int kiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

int sqAttacked(const int sq, const int side, const S_BOARD* pos){
    int pce, index, t_sq, dir;

    ASSERT(sqOnBoard(sq));
    ASSERT(sideValid(side));
    ASSERT(checkBoard(pos));

    // Pawns
    if(side == WHITE){
        if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP){
            return TRUE;
        }
    } else{
        if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP){
            return TRUE;
        }
    }

    // Knights
    for(index = 0; index < 8; ++index){
        pce = pos->pieces[sq + knDir[index]];
        if(isKn(pce) && pieceCol[pce] == side){
            return TRUE;
        }
    }

    // Rooks
    for(index = 0; index < 4; ++index){
        dir = rkDir[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while(pce != OFFBOARD){
            if(pce != EMPTY){
                if(isRQ(pce) && pieceCol[pce] == side){
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // Bishops
    for(index = 0; index < 4; ++index){
        dir = biDir[index];
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];
        while(pce != OFFBOARD){
            if(pce != EMPTY){
                if(isBQ(pce) && pieceCol[pce] == side){
                    return TRUE;
                }
                break;
            }
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    // Kings
    for(index = 0; index < 8; ++index){
        pce = pos->pieces[sq + kiDir[index]];
        if(isKi(pce) && pieceCol[pce] == side){
            return TRUE;
        }
    }

    return FALSE;
}