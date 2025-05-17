#include "defs.h"

int main(void) {

  allInit();
  int index = 0;
  U64 playBitBoard = 0ULL;

  printf("\n");
  SETBIT(playBitBoard, 61);
  printBitBoard(playBitBoard);

  printf("\n");
  CLRBIT(playBitBoard, 61);
  printBitBoard(playBitBoard);

  return EXIT_SUCCESS;
}
