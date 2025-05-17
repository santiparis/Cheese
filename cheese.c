#include "defs.h"

int main(void) {

  int index = 0;

  allInit();

  for(index = 0; index < BRD_SQ_NUM; ++index){
    if(index%10 == 0) printf("\n");
    printf("%5d ", sq120ToSq64[index]);
  }

  printf("\n\n");

  for(index = 0; index < 64; ++index){
    if(index%8 == 0) printf("\n");
    printf("%5d ", sq64ToSq120[index]);
  }

  return 0;
}
