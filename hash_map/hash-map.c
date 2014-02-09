#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "int-array.h"
#include "strhash.h"

// 1. All constructors should take pointers so the user
// can allocate structs on the stack or the heap.

// 2. KV pairs should be structs

// initialization

typedef struct {
  Array store;
  int numElems;
} HashMap;

void _makeBuckets(HashMap* hashPtr) {
  int i;

  for (i = 0; i < hashPtr->store.storeLimit; i++) {
    Array* ptrToBucket = malloc(sizeof(Array));
    makeArray(ptrToBucket);
    push(&hashPtr->store, ptrToBucket);
    ptrToBucket->id = hashPtr->store.storeSize;
  }
}

void makeHashMap(HashMap* hashPtr) {
  Array* newStorePtr = malloc(sizeof(Array));
  hashPtr->store = *newStorePtr;
  makeArray(&hashPtr->store);
  _makeBuckets(hashPtr);
  hashPtr->numElems = 0;
}

// manipulation

Array* _forEl(HashMap* hashPtr, char key) {
  char* keyString = malloc(sizeof(char) + 1);
  keyString[0] = key;
  keyString[1] = '\0';
  uint32_t hashedKey = SuperFastHash(keyString, 1);
  int bucketIndex = hashedKey % hashPtr->store.storeSize;
  Array* bucketPtr = (Array*) valueAt(&hashPtr->store, bucketIndex);

  return bucketPtr;
}

typedef struct {
  char key;
  int value;
} KVPair;

// TODO: check for inclusion before adding
void add(HashMap* hashPtr, char key, int value) {
  Array* bucketPtr = _forEl(hashPtr, key);
  KVPair* kvPairPtr = malloc(sizeof(KVPair));
  kvPairPtr->key = key;
  kvPairPtr->value = value;

  push(bucketPtr, kvPairPtr);
  Array* retrievedPairPtr = (Array*) valueAt(bucketPtr, bucketPtr->storeSize - 1);
  printf("added pair with store address %p\n", &retrievedPairPtr->store);
}

int find(HashMap* hashPtr, char key) {
  if (hashPtr->store.storeSize < 1) {
    printf("hash is empty");
    return 0;
  }
  Array* bucketPtr = _forEl(hashPtr, key);
  int i;
  for (i = 0; i < bucketPtr->storeSize; i++) {
    KVPair* thisPairPtr = (KVPair*) valueAt(bucketPtr, i);
    if (thisPairPtr->key == key) {
      return thisPairPtr->value;
    }
  }
  printf("nothing found for key %c\n", key);
  return 0;
}

int main() {
  HashMap* myHashPtr = malloc(sizeof(HashMap));
  makeHashMap(myHashPtr);


  add(myHashPtr, 'a', 1);
  add(myHashPtr, 'b', 2);
  add(myHashPtr, 'c', 3);
  /*
  add(&myHash, 'd', 4);
  add(&myHash, 'e', 5);
  add(&myHash, 'f', 6);
  add(&myHash, 'g', 7);
  */

  int one = find(myHashPtr, 'a');
  int two = find(myHashPtr, 'b');
  int three = find(myHashPtr, 'c');

  printf("value two has key %d\n", two);
  printf("value three has key %d\n", three);
  printf("value one has key %d\n", one);

  return 0;
}
