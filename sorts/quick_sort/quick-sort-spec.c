#include <stdlib.h>
#include <assert.h>
#include "quick-sort.h"

int numsEq(void* src[], void* targ[], int len) {
  int i;

  for (i = 0; i < len; i++){
    int* sourceElPtr = (int*) src[i];
    int* targElPtr = (int*) targ[i];
    if (*sourceElPtr != *targElPtr) {
      return 0;
    }
  }

  return 1;
}

int ascending(void* aPtr, void* bPtr) {
  int a = *(int*) aPtr, b = *(int*) bPtr;
  return a > b;
}

int descending(void* aPtr, void* bPtr) {
  int a = *(int*) aPtr,
      b = *(int*) bPtr;
  return a < b;
}

void copyPtrs(void** ptrs , int vals[], int len) {
  int i;
  for (i = 0; i < len; i++) {
    ptrs[i] = &vals[i];
  }
}

int main() {
  int len;
  void** pointersOrig, * pointersExpected;

  // it sorts lists with one element
  len = 1;
  int oneEl[] = { 1 };
  int oneElExpected[] = { 1 };
  pointersOrig = malloc(sizeof(void*) * len);
  pointersExpected = malloc(sizeof(void*) * len);
  copyPtrs(pointersOrig, oneEl, len);
  copyPtrs(pointersExpected, oneElExpected, len);
  quickSort(pointersOrig, len, (int (*)(void*, void*)) ascending);

  assert( numsEq(pointersExpected, pointersOrig, len) );
  free(pointersOrig);
  free(pointersExpected);

  // it sorts lists with duplicate elements
  len = 3;
  int dups[] = { 1, 1, 1 };
  int dupsExpectd[] = { 1, 1, 1};
  pointersOrig = malloc(sizeof(void*) * len);
  pointersExpected = malloc(sizeof(void*) * len);
  copyPtrs(pointersOrig, dups, len);
  copyPtrs(pointersExpected, dupsExpectd, len);
  quickSort(pointersOrig, len, (int (*)(void*, void*)) ascending);

  assert( numsEq(pointersExpected, pointersOrig, len) );
  free(pointersOrig);
  free(pointersExpected);

  // it sorts odd-numbered lists
  len = 5;
  int oddNums[] = { 5, 4, 3, 2, 1 };
  int oddExpected[] = { 1, 2, 3, 4, 5 };
  pointersOrig = malloc(sizeof(void*) * len);
  pointersExpected = malloc(sizeof(void*) * len);
  copyPtrs(pointersOrig, oddNums, len);
  copyPtrs(pointersExpected, oddExpected, len);
  quickSort(pointersOrig, len, (int (*)(void*, void*)) ascending);

  assert( numsEq(pointersExpected, pointersOrig, len) );
  free(pointersOrig);
  free(pointersExpected);

  // it sorts even-numbered lists
  len = 6;
  int evenNums[] = { 6, 5, 4, 3, 2, 1 };
  int evenExpected[] = { 1, 2, 3, 4, 5, 6 };
  pointersOrig = malloc(sizeof(void*) * len);
  pointersExpected = malloc(sizeof(void*) * len);
  copyPtrs(pointersOrig, evenNums, len);
  copyPtrs(pointersExpected, evenExpected, len);
  quickSort(pointersOrig, len, (int (*)(void*, void*)) ascending);

  assert( numsEq(pointersExpected, pointersOrig, len) );
  free(pointersOrig);
  free(pointersExpected);

  // it sorts elements in a specified order
  len = 6;
  int elements[] = { 6, 5, 4, 3, 2, 1 };
  int elementsExpected[] = { 6, 5, 4, 3, 2, 1 };
  pointersOrig = malloc(sizeof(void*) * len);
  pointersExpected = malloc(sizeof(void*) * len);
  copyPtrs(pointersOrig, elements, len);
  copyPtrs(pointersExpected, elementsExpected, len);
  quickSort(pointersOrig, len, (int (*)(void*, void*)) descending);

  assert( numsEq(pointersExpected, pointersOrig, len) );
  free(pointersOrig);
  free(pointersExpected);

  return 0;
}

