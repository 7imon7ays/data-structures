#include "array-header.h"

int main(int argc, char* argv[]) {
  Array* myArrPtr = malloc(sizeof(Array));
  makeArray(myArrPtr);

  int i;

  for (i = 0; i < 40; i++) {
    int* valuePtr = malloc(sizeof(int));
    *valuePtr = i;
    push(myArrPtr, valuePtr);
  }

  int* twentiethPtr = (int*) valueAt(myArrPtr, 20);
  int* thirtyfifthPtr = (int*) valueAt(myArrPtr, 35);
  printf("Index 20 has value %d\n", *twentiethPtr);
  printf("Index 35 has value %d\n", *thirtyfifthPtr);

  for (i = 0; i < myArrPtr->storeSize; i++) {
    free(valueAt(myArrPtr, i));
  }

  free(myArrPtr);

  return 0;
}
