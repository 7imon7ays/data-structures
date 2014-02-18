#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "int-array.h"
#include "strhash.h"


// initialization with hashing and comparison
// functions for each type.

typedef struct {
  Array store;
  int numElems;
  int maxElemsPerBucket;

  int (*eq)(void*, void*);
  int (*hash)(void*);
} HashMap;

int intEq(int* ip1, int* ip2) {
  return (*ip1 == *ip2 ? 1 : 0);
}

int intHash(int* ip1) {
  return SuperFastHash(ip1, sizeof(int));
}

typedef struct {
  int x;
  int y;
} Coordinate;

int coordinateEq(Coordinate* cp1, Coordinate* cp2) {
  return ((cp1->x == cp2->x) || (cp1->y == cp2->y)) ? 1 : 0;
}

int coordinateHash(Coordinate* cp1) {
  return SuperFastHash(cp1, sizeof(Coordinate));
}

int strEq(char* str1, char* str2) {
  return strcmp(str1, str2) == 0 ? 1 : 0;
}

int strHash(char* sp1) {
  int strLen = strlen(sp1);
  return SuperFastHash(sp1, strLen);
}

void _makeBuckets(HashMap* hashPtr) {
  int i;

  for (i = 0; i < hashPtr->store.storeLimit; i++) {
    Array* ptrToBucket = malloc(sizeof(Array));
    makeArray(ptrToBucket);
    push(&hashPtr->store, ptrToBucket);
    ptrToBucket->id = hashPtr->store.storeSize;
  }
}

void makeHashMap(
      HashMap* hashPtr,
      int (*eq)(void*, void*),
      int (*hash)(void*)
    ) {
  hashPtr->numElems = 0;
  hashPtr->maxElemsPerBucket = 1;
  Array* newStorePtr = malloc(sizeof(Array));
  hashPtr->store = *newStorePtr;
  makeArray(&hashPtr->store);
  _makeBuckets(hashPtr);
  hashPtr->numElems = 0;

  hashPtr->eq = eq;
  hashPtr->hash = hash;
}

// manipulation

Array* _forEl(HashMap* hashPtr, void* keyPtr) {
  uint32_t hashedKey = hashPtr->hash(keyPtr);
  int bucketIndex = hashedKey % hashPtr->store.storeSize;
  Array* bucketPtr = (Array*) valueAt(&hashPtr->store, bucketIndex);

  return bucketPtr;
}

typedef struct {
  void* keyPtr;
  void* valuePtr;
} KVPair;


void* find(HashMap* hashPtr, void* keyPtr) {
  assert(hashPtr->store.storeSize != 0);

  Array* bucketPtr = _forEl(hashPtr, keyPtr);
  int i;
  for (i = 0; i < bucketPtr->storeSize; i++) {
    KVPair* thisPairPtr = (KVPair*) valueAt(bucketPtr, i);
    if (hashPtr->eq(thisPairPtr->keyPtr, keyPtr)) {
      return thisPairPtr->valuePtr;
    }
  }
  printf("nothing found for key %s\n", (char*) keyPtr);
  int* nullPtr = malloc(sizeof(int));
  *nullPtr = 0;
  return nullPtr;
}

void resizeHash(HashMap* hashPtr) {

}

// TODO return if key already exists with that value.
void add(HashMap* hashPtr, void* keyPtr, void* valuePtr) {
  if (hashPtr->numElems / hashPtr->store.storeSize >
      hashPtr->maxElemsPerBucket) {
    resizeHash(hashPtr);
  }

  Array* bucketPtr = _forEl(hashPtr, keyPtr);
  KVPair* kvPairPtr = malloc(sizeof(KVPair));
  kvPairPtr->keyPtr = keyPtr;
  kvPairPtr->valuePtr = valuePtr;

  push(bucketPtr, kvPairPtr);
  hashPtr->numElems++;
}

int main() {
  HashMap* myHashPtr = malloc(sizeof(HashMap));
  makeHashMap(
    myHashPtr,
    (int (*)(void*, void*)) strEq,
    (int (*)(void*)) strHash);

  // add key "keyA" with value 1
  char* key1Ptr = malloc(sizeof(char) * 5);
  int* value1Ptr = malloc(sizeof(int*));
  key1Ptr = "keyA";
  *value1Ptr = 1;
  add(myHashPtr, key1Ptr, value1Ptr);

  // add key "keyB" with value 'b'
  char* key2Ptr = malloc(sizeof(char) * 3);
  char* value2Ptr = malloc(sizeof(char));
  key2Ptr = "keyB";
  *value2Ptr = 'b';
  add(myHashPtr, key2Ptr, value2Ptr);

  // look up keys "keyA" and "kB". Also look up absent key.
  int* onePtr = find(myHashPtr, "keyA");
  char* twoPtr = find(myHashPtr, "keyB");
  int* nonePtr = find(myHashPtr, "none");

  printf("key %s has value %d\n", "keyA", *onePtr);
  printf("key %s has value %c\n", "kB", *twoPtr);
  printf("key 'none' has value %d\n", *nonePtr);

  return 0;
}
