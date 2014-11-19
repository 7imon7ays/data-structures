#include <assert.h>
#include "quick-sort.h"

int numsEq(int* src, int* targ, int len) {
  int i;

  for (i = 0; i < len; i++){
    if (src[i] != targ[i]) {
      return 0;
    }
  }

  return 1;
}

int main() {
  int len;

  // it sorts lists with one element
  len = 1;
  int oneEl[] = { 1 };
  int oneElExpected[] = { 1 };
  qsort(oneEl, len);

  assert( numsEq(oneElExpected, oneEl, len) );

  // it sorts lists with duplicate elements
  len = 3;
  int dups[] = { 1, 1, 1 };
  int dupsExpectd[] = { 1, 1, 1};
  qsort(dups, len);

  assert( numsEq(dupsExpectd, dups, len) );

  // it sorts odd-numbered lists
  len = 5;
  int oddNums[] = { 5, 4, 3, 2, 1 };
  int oddExpected[] = { 1, 2, 3, 4, 5 };
  qsort(oddNums, len);

  assert (numsEq(oddExpected, oddNums, len));

  // it sorts even-numbered lists
  len = 6;
  int evenNums[] = { 6, 5, 4, 3, 2, 1 };
  int evenExpected[] = { 1, 2, 3, 4, 5, 6 };
  qsort(evenNums, len);

  assert (numsEq(evenExpected, evenNums, len));

  return 0;
}

