#include "../c_hash_map/hash-header.h"

int main() {
  HashMap* myHashPtr = malloc(sizeof(HashMap));
  makeHashMap(
      myHashPtr,
      (int (*)(void*, void*)) intEq,
      (int (*)(void*)) intHash);

  int i;
  int j;
  for (i= 0; i < 100; i++, j++) {
    int* keyPtr = malloc(sizeof(int));
    int* valuePtr = malloc(sizeof(int));
    *keyPtr = i;
    *valuePtr = j;
    add(myHashPtr, keyPtr, valuePtr);
  }

  int twenty = 20;
  int* valueAtTwentyPtr = (int*) find(myHashPtr, &twenty);
  assert(*valueAtTwentyPtr == 20);

  int unmapped = 101;
  int* unmappedValuePtr = (int*) find(myHashPtr, &unmapped);
  assert(*unmappedValuePtr == 0);

  // freeHashMap(myHashPtr)

  return 0;
}

