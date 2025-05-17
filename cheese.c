#include "defs.h"

int main(void) {

    allInit();

    int move = 0;
    int from = A2; int to = H7;
    int cap = wR; int prom = bK;

    move = (from) | (to << 7) | (cap << 14) | (prom << 20);

    printf("from: %d to: %d cap: %d prom: %d\n",
        FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));

    printf("Algebraic from: %s\n", ptSq(from));
    printf("Algebraic to: %s\n", ptSq(to));
    printf("Algebraic from: %s\n", ptMove(move));

    return EXIT_SUCCESS;
}
