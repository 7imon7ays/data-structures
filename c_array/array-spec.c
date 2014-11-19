#include "./array-header.h"

int main(int argc, char* argv[]) {
  Array* myArrPtr = malloc(sizeof(Array));
  makeArray(myArrPtr);

  int i;

  for (i = 0; i < 40; i++) {
    int* valuePtr = malloc(sizeof(int));
    *valuePtr = i;
    push(myArrPtr, valuePtr);
  }

  Array* nestedArrPtr = malloc(sizeof(Array));
  makeArray(nestedArrPtr);
  push(myArrPtr, nestedArrPtr);

  int* twentiethPtr = (int*) valueAt(myArrPtr, 20);
  int* thirtyfifthPtr = (int*) valueAt(myArrPtr, 35);
  Array* retrivedNestedArrPtr = valueAt(myArrPtr, 40);

  assert(*twentiethPtr == 20);
  assert(*thirtyfifthPtr == 35);
  assert( sizeof(*retrivedNestedArrPtr) == sizeof(*nestedArrPtr) );

  freeArray(myArrPtr);

  return 0;
}
