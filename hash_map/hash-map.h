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

void _makeBuckets(Array* arrayPtr, int numBuckets) {
  int i;

  for (i = 0; i < numBuckets; i++) {
    Array* ptrToBucket = malloc(sizeof(Array));
    makeArray(ptrToBucket);
    push(arrayPtr, ptrToBucket);
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
  _makeBuckets(&hashPtr->store, 10);
  hashPtr->numElems = 0;

  hashPtr->eq = eq;
  hashPtr->hash = hash;
}

// manipulation

Array* _forEl(Array* storePtr, int (*hash)(void*), void* keyPtr) {
  uint32_t hashedKey = hash(keyPtr);
  int bucketIndex = hashedKey % storePtr->storeSize;
  Array* bucketPtr = (Array*) valueAt(storePtr, bucketIndex);

  return bucketPtr;
}

typedef struct {
  void* keyPtr;
  void* valuePtr;
} KVPair;


void* find(HashMap* hashPtr, void* keyPtr) {
  assert(hashPtr->store.storeSize != 0);

  Array* bucketPtr = _forEl(&(hashPtr->store), hashPtr->hash, keyPtr);
  int i;
  for (i = 0; i < bucketPtr->storeSize; i++) {
    KVPair* thisPairPtr = (KVPair*) valueAt(bucketPtr, i);
    if (hashPtr->eq(thisPairPtr->keyPtr, keyPtr)) {
      return thisPairPtr->valuePtr;
    }
  }

  int* nullPtr = malloc(sizeof(int));
  *nullPtr = 0;
  return nullPtr;
}

void resizeHash(HashMap* hashPtr) {
  printf("resizing hash \n");

  Array* oldStorePtr = &hashPtr->store;
  Array* newStorePtr = malloc(sizeof(Array));
  makeArray(newStorePtr);

  _makeBuckets(newStorePtr, oldStorePtr->storeSize * 2);

  printf("made buckets\n");

  int i;
  int numBuckets = oldStorePtr->storeSize;
  for (i = 0; i < numBuckets; i++) {
    Array* oldBucketPtr = (Array*) valueAt(oldStorePtr, i);
    printf("found old bucket at index %d\n", i);
    int j;
    for (j = 0; j < oldBucketPtr->storeSize; j++) {
      printf("store size is %d\n", oldBucketPtr->storeSize);
      KVPair* kvPairPtr = (KVPair*) valueAt(oldBucketPtr, j);
      printf("found kv pair with key %d\n", *((int*) kvPairPtr->keyPtr));
      Array* newBucketPtr = _forEl(newStorePtr, hashPtr->hash, kvPairPtr->keyPtr);
      push(newBucketPtr, kvPairPtr);
    }
  }

  hashPtr->store = *newStorePtr;
  //free(oldStorePtr); TODO: fix freeing
  printf("to a store limit of %d\n", hashPtr->store.storeLimit);
}

void add(HashMap* hashPtr, void* keyPtr, void* valuePtr) {
  if ( (float) hashPtr->numElems / hashPtr->store.storeSize >
      hashPtr->maxElemsPerBucket ) {
    resizeHash(hashPtr);
  }

  void* foundValuePtr = find(hashPtr, keyPtr);
  if (hashPtr->eq(valuePtr, foundValuePtr)) {
    printf("Same value already at that key\n");
    return;
  }

  Array* bucketPtr = _forEl(&(hashPtr->store), hashPtr->hash, keyPtr);
  KVPair* kvPairPtr = malloc(sizeof(KVPair));
  kvPairPtr->keyPtr = keyPtr;
  kvPairPtr->valuePtr = valuePtr;

  push(bucketPtr, kvPairPtr);
  hashPtr->numElems++;
}

// Testing
/*
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

  // add same value for "keyA" to test against redundancy
  add(myHashPtr, key1Ptr, value1Ptr);

  // look up keys "keyA" and "kB". Also look up absent key.
  int* onePtr = find(myHashPtr, "keyA");
  char* twoPtr = find(myHashPtr, "keyB");
  int* nonePtr = find(myHashPtr, "none");

  printf("key %s has value %d\n", "keyA", *onePtr);
  printf("key %s has value %c\n", "kB", *twoPtr);
  printf("key 'none' has value %d\n", *nonePtr);

  free(myHashPtr);
  free(value1Ptr);
  free(value2Ptr);

  return 0;
}
*/
