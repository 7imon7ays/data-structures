#include "./quick-sort.h"
#include <stdio.h>

int main() {
  int nums[] = { 5, 4, 0, 2, 1 },
      i, left, right, len = 5;

  for (i = 0; i < len; i++) {
    printf("%d", nums[i]);
  }
  printf("\n");

  int firstNum = nums[0];

  qsort(&firstNum, len);

  for (i = 0; i < len; i++) {
    printf("%d", nums[i]);
  }
  printf("\n");

  return 0;
}

