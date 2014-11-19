#include "./quick-sort.h"
#include <stdio.h>

int main() {
  int nums[] = { 6, 5, 6, 2, 3, 4 },
      i, len = 6;

  for (i = 0; i < len; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  qsort(nums, len);

  for (i = 0; i < len; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  return 0;
}

