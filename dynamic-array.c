#include <stdlib.h>
#include <stdio.h>

typedef struct {
  int storeSize;
  int storeLimit;
  void** store;
} Array;

Array makeArray() {
  Array arr;
  arr.storeSize = 0;
  arr.storeLimit = 10;
  arr.store = malloc(sizeof(void*) * 5);
  return arr;
}

void* valueAt(Array arr, int index) {
  return *(arr.store + index);
}

void copy(void** from, void** to) {
  int i;
  unsigned long arrSize = sizeof(from) / sizeof(int);
  for (i = 0; i < arrSize; i++) {
    to[i] = from[i];
  }
}

void resize(Array* arrPtr) {
  arrPtr->storeLimit = arrPtr->storeLimit * 2;
  int* newStore = malloc(sizeof(void*) * arrPtr->storeLimit);
  copy(arrPtr->store, newStore);
  free(arrPtr->store);
  arrPtr->store = newStore;
}


void push(Array* arrPtr, void* valuePtr) {
  if (arrPtr->storeSize + 1 > arrPtr->storeLimit) {
    resize(arrPtr);
  }

  arrPtr->store[arrPtr->storeSize] = valuePtr;
  arrPtr->storeSize++;

  return *valuePtr;
}

int main(int argc, char* argv[]) {
  Array myArray = makeArray();

  int i;
  for (i = 0; i < 100; i++) {
    push(&myArray, i);
  }
  push(&myArray, "hello");

  void* intElement = valueAt(myArray, 99);
  void* strElement = valueAt(myArray, 100);

  printf("second to last element: %d\n", (int)intElement);
  printf("last element: %s\n", (char*)strElement);

  return 0;
}
