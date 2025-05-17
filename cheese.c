#include "defs.h"

int main(void) {

  allInit();

  U64 playBitBoard = 0ULL;

  playBitBoard |= (1ULL << SQ64(D2));
  playBitBoard |= (1ULL << SQ64(D3));
  playBitBoard |= (1ULL << SQ64(D4));

  printf("\n");
  printBitBoard(playBitBoard);

  int sq64 = 0;
  while(playBitBoard){
    sq64 = POP(&playBitBoard);

    printf("Popped: %d\n", sq64);
    printBitBoard(playBitBoard);
  }

  printf("\n");

  return EXIT_SUCCESS;
}
