#include "defs.h"

#define MOVE(f, t, ca, pro, fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq) (filesBrd[(sq)] == OFFBOARD)

void addQuietMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addCaptureMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addEnPassantMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addWhitePawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list){
    if(ranksBrd[from] == RANK_7){
        addCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void addWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){
    if(ranksBrd[from] == RANK_7){
        addCaptureMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void addBlackPawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list){
    if(ranksBrd[from] == RANK_2){
        addCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void addBlackPawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){
    if(ranksBrd[from] == RANK_2){
        addCaptureMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void generateAllMoves(const S_BOARD* pos, S_MOVELIST* list){
    ASSERT(checkBoard(pos));

    list->count = 0;

    int pce = EMPTY;
    int side = pos->side;
    int sq = 0; int t_sq = 0;
    int pceNum = 0;

    if(side == WHITE){
        for(pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum){
            sq = pos->pList[wP][pceNum];
            ASSERT(sqOnBoard(sq));

            if(pos->pieces[sq + 10] == EMPTY){
                addWhitePawnMove(pos, sq, sq+10, list);
                if(ranksBrd[sq] == RANK_2 && pos->pieces[sq+20] == EMPTY){
                    addQuietMove(pos, MOVE(sq, sq+20, EMPTY, EMPTY, MFLAGPS), list);
                }
            }

            if(!SQOFFBOARD(sq + 9) && pieceCol[pos->pieces[sq+9]] == BLACK){
                addWhitePawnCapMove(pos, sq, sq+9, pos->pieces[sq+9], list);
            }
            if(!SQOFFBOARD(sq + 11) && pieceCol[pos->pieces[sq+11]] == BLACK){
                addWhitePawnCapMove(pos, sq, sq+11, pos->pieces[sq+11], list);
            }

            if(sq + 9 == pos->enPas){
                addCaptureMove(pos, MOVE(sq, sq+9, EMPTY, EMPTY, MFLAGEP), list);
            }
            if(sq + 11 == pos->enPas){
                addCaptureMove(pos, MOVE(sq, sq+11, EMPTY, EMPTY, MFLAGEP), list);
            }
        }
    } else{
        for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum){
            sq = pos->pList[bP][pceNum];
            ASSERT(sqOnBoard(sq));

            if(pos->pieces[sq - 10] == EMPTY){
                addBlackPawnMove(pos, sq, sq-10, list);
                if(ranksBrd[sq] == RANK_7 && pos->pieces[sq-20] == EMPTY){
                    addQuietMove(pos, MOVE(sq, sq-20, EMPTY, EMPTY, MFLAGPS), list);
                }
            }

            if(!SQOFFBOARD(sq - 9) && pieceCol[pos->pieces[sq-9]] == WHITE){
                addBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq-9], list);
            }
            if(!SQOFFBOARD(sq - 11) && pieceCol[pos->pieces[sq-11]] == WHITE){
                addBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq-11], list);
            }

            if(sq - 9 == pos->enPas){
                addCaptureMove(pos, MOVE(sq, sq-9, EMPTY, EMPTY, MFLAGEP), list);
            }
            if(sq - 11 == pos->enPas){
                addCaptureMove(pos, MOVE(sq, sq-11, EMPTY, EMPTY, MFLAGEP), list);
            }
        }
    }
}