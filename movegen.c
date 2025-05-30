#include "defs.h"

#define MOVE(f, t, ca, pro, fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq) (filesBrd[(sq)] == OFFBOARD)

const int loopSlidePce[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};

const int loopNonSlidePce[6] = {wN, wK, 0, bN, bK, 0};

const int loopNonSlideIndex[2] = {0, 3};

const int loopSlideIndex[2] = {0, 4};

int pceDir[13][8] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {-8,-19,-21,-12,8,19,21,12},
    {-9,-11,11,9,0,0,0,0},
    {-1,-10,1,10,0,0,0,0},
    {-1,-10,1,10,-9,-11,11,9},
    {-1,-10,1,10,-9,-11,11,9},
    {0,0,0,0,0,0,0},
    {-8,-19,-21,-12,8,19,21,12},
    {-9,-11,11,9,0,0,0,0},
    {-1,-10,1,10,0,0,0,0},
    {-1,-10,1,10,-9,-11,11,9},
    {-1,-10,1,10,-9,-11,11,9}
};

int numDir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

static void addQuietMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

static void addCaptureMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

static void addEnPassantMove(const S_BOARD* pos, int move, S_MOVELIST* list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

static void addWhitePawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list){

    ASSERT(pieceValidEmpty(cap));
    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

    if(ranksBrd[from] == RANK_7){
        addCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void addWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){

    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

    if(ranksBrd[from] == RANK_7){
        addCaptureMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
        addCaptureMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

static void addBlackPawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list){

    ASSERT(pieceValidEmpty(cap));
    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

    if(ranksBrd[from] == RANK_2){
        addCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        addCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
    } else{
        addCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void addBlackPawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){

    ASSERT(sqOnBoard(from));
    ASSERT(sqOnBoard(to));

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
    int dir = 0;
    int index = 0;
    int pceIndex = 0;

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

        if(pos->castlePerm & WKCA){
            if(pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY){
                if(!sqAttacked(E1, BLACK, pos) && !sqAttacked(F1, BLACK, pos) && !sqAttacked(G1, BLACK, pos)){
                    addQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }

        if(pos->castlePerm & WQCA){
            if(pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY){
                if(!sqAttacked(C1, BLACK, pos) && !sqAttacked(D1, BLACK, pos) && !sqAttacked(E1, BLACK, pos)){
                    addQuietMove(pos, MOVE(E1, C1, EMPTY, EMPTY, MFLAGCA), list);
                }
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

        if(pos->castlePerm & BKCA){
            if(pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY){
                if(!sqAttacked(E8, WHITE, pos) && !sqAttacked(F8, WHITE, pos) && !sqAttacked(G8, WHITE, pos)){
                    addQuietMove(pos, MOVE(E8, G8, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }

        if(pos->castlePerm & BQCA){
            if(pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY){
                if(!sqAttacked(C8, WHITE, pos) && !sqAttacked(D8, WHITE, pos) && !sqAttacked(E8, WHITE, pos)){
                    addQuietMove(pos, MOVE(E8, C8, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }
    }

    // Loop for slide pieces

    pceIndex = loopSlideIndex[side];
    pce = loopSlidePce[pceIndex++];

    while(pce != 0){
        ASSERT(pieceValid(pce));
        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            ASSERT(sqOnBoard(sq));

            for(index = 0; index < numDir[pce]; ++index){
                dir = pceDir[pce][index];
                t_sq = sq + dir;

                while(!SQOFFBOARD(t_sq)){

                    if(pos->pieces[t_sq] != EMPTY){
                        if(pieceCol[pos->pieces[t_sq]] == side ^ 1) addCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                        break;
                    }
                    addQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
                    t_sq += dir;
                }
            }
        }
        pce = loopSlidePce[pceIndex++];
    }

    // Loop for non sliders

    pceIndex = loopNonSlideIndex[side];
    pce = loopNonSlidePce[pceIndex++];

    while(pce != 0){
        ASSERT(pieceValid(pce));
        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            ASSERT(sqOnBoard(sq));

            for(index = 0; index < numDir[pce]; ++index){
                dir = pceDir[pce][index];
                t_sq = sq + dir;

                if(SQOFFBOARD(t_sq)) continue;

                if(pos->pieces[t_sq] != EMPTY){
                    if(pieceCol[pos->pieces[t_sq]] == side ^ 1) if(pieceCol[pos->pieces[t_sq]] == side ^ 1) addCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                    continue;
                }
                addQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
            }
        }
        pce = loopNonSlidePce[pceIndex++];
    }
}