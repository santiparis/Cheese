#include "defs.h"

int main(void) {

  U64 playBitBoard = 0ULL;

  allInit();

  printf("Start: \n\n");
  printBitBoard(playBitBoard);

  playBitBoard |= (1ULL << SQ64(D2));

  printf("D2 Added: \n\n");
  printBitBoard(playBitBoard);

  playBitBoard |= (1ULL << SQ64(G2));

  printf("G2 Added: \n\n");
  printBitBoard(playBitBoard);

  return 0;
}
