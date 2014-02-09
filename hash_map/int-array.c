#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
  int id;
  int storeSize;
  int storeLimit;
  void** store;
} Array;

void makeArray(Array* arrPtr) {
  arrPtr->storeSize = 0;
  arrPtr->storeLimit = 10;
  arrPtr->store = malloc(sizeof(void*) * arrPtr->storeLimit);
}

int* valueAt(Array arr, int index) {
  return *(arr.store + index);
}

void copy(void** from, void** to, int numEls) {
  int i;
  for (i = 0; i < numEls; i++) {
    to[i] = from[i];
  }
}

void resize(Array* arrPtr) {
  printf("resizing array from %d max to ", arrPtr->storeLimit);
  arrPtr->storeLimit = arrPtr->storeLimit * 2;
  int* newStore = malloc(sizeof(void*) * arrPtr->storeLimit);
  copy(arrPtr->store, (void*) newStore, arrPtr->storeSize);
  free(arrPtr->store);
  arrPtr->store = (void**) newStore;
  printf("%d max\n", arrPtr->storeLimit);
}


void push(Array* arrPtr, void* valuePtr) {
  if (arrPtr->storeSize + 1 > arrPtr->storeLimit) {
    resize(arrPtr);
  }

  arrPtr->store[arrPtr->storeSize] = valuePtr;
  arrPtr->storeSize++;
  assert( arrPtr->storeSize <= arrPtr->storeLimit);
}

int main() {
  Array* ptrToMyArr = malloc(sizeof(Array));
  makeArray(ptrToMyArr);

  int i;
  for (i = 0; i < 100; i++) {
    int* jPtr = malloc(sizeof(int));
    *jPtr = i;
    push(ptrToMyArr, jPtr);
  }

  int testIndex = 30;
  printf("at index %d: %d\n", testIndex, *valueAt(*ptrToMyArr, testIndex));
}
