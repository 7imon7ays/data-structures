#include "hash-map.h"

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
    printf("hash now has %d els and %d buckets\n",
        myHashPtr->numElems,
        myHashPtr->store.storeSize);
  }
}
