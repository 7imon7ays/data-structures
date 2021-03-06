#include "./quick-sort.h"
#include <stdlib.h>
#include <stdio.h>

void copyPtrs(void** ptrs, int vals[], int len) {
  int i;
  for (i = 0; i < len; i++) {
    ptrs[i] = &vals[i];
  }
}

int main() {
  int nums[] = { 6, 5, 6, 2, 3, 4 },
      i, len = 6;

  for (i = 0; i < len; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  void** pointers = malloc(sizeof(void*) * len);
  copyPtrs(pointers, nums, len);

  quickSort(pointers, len, 1, (int (*)(void*, void*)) descending);

  for (i = 0; i < len; i++) {
    printf("%d ", *(int*) pointers[i]);
  }
  printf("\n");

  return 0;
}

