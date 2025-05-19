#include "defs.h"

#define MOVE(f, t, ca, pro, fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq) (filesBrd[(sq)] == OFFBOARD)

int loopSlidePce[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};

int loopNonSlidePce[6] = {wN, wK, 0, bN, bK, 0};

int loopNonSlideIndex[2] = {0, 3};

int loopSlideIndex[2] = {0, 4};

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

void addWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){

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

void addBlackPawnCapMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* list){

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

void addBlackPawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* list){

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

    printf("\n\nSide: %d\n", side);

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

    // Loop for slide pieces

    pceIndex = loopSlideIndex[side];
    pce = loopSlidePce[pceIndex++];

    while(pce != 0){
        ASSERT(pieceValid(pce));
        printf("Sliders pceIndex: %d pce: %d\n", pceIndex, pce);
        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            printf("Piece number: %d\n", pos->pceNum[pce]);
            ASSERT(sqOnBoard(sq));
            printf("Piece: %c on %s\n", pceChar[pce], ptSq(sq));

            for(index = 0; index < numDir[pce]; ++index){
                dir = pceDir[pce][index];
                t_sq = sq + dir;

                while(!SQOFFBOARD(t_sq)){

                    if(pos->pieces[t_sq] != EMPTY){
                        if(pieceCol[pos->pieces[t_sq]] == side ^ 1) printf("\t\tCapture on %s\n", ptSq(t_sq));
                        break;
                    }
                    printf("\t\tNormal to %s\n", ptSq(t_sq));
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
        printf("Non sliders pceIndex: %d pce: %d\n", pceIndex, pce);

        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            printf("Piece number: %d\n", pos->pceNum[pce]);
            ASSERT(sqOnBoard(sq));
            printf("Piece: %c on %s\n", pceChar[pce], ptSq(sq));

            for(index = 0; index < numDir[pce]; ++index){
                dir = pceDir[pce][index];
                t_sq = sq + dir;

                if(SQOFFBOARD(t_sq)) continue;

                if(pos->pieces[t_sq] != EMPTY){
                    if(pieceCol[pos->pieces[t_sq]] == side ^ 1) printf("\t\tCapture on %s\n", ptSq(t_sq));
                    continue;
                }
                printf("\t\tNormal to %s\n", ptSq(t_sq));
            }
        }
        pce = loopNonSlidePce[pceIndex++];
    }
}