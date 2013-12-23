#include "header.h"


// initialization

typedef struct {
  Array store;
  int numBuckets;
  int numElems;
} HashMap;

void makeBuckets(HashMap* hashPtr) {
  HashMap hashMap = *hashPtr;
  int i;

  Array* bucketHolder = malloc(hashMap.numBuckets * sizeof(Array));

  for (i = 0; i < hashMap.numBuckets; i++) {
    bucketHolder[i] = makeArray();
    push(&hashMap.store, &bucketHolder[i]);
  }
}

HashMap makeHashMap() {
  HashMap newHashMap;
  newHashMap.store = makeArray();
  newHashMap.numBuckets = 10;
  makeBuckets(&newHashMap);
  newHashMap.numElems = 0;

  return newHashMap;
}

// manipulation

Array* forEl(HashMap* hashPtr, char* key) {
  int len;
  for (len = 0; key[len] != '\0'; len++) {}
  uint32_t hashedKey = SuperFastHash(key, len);
  int bucketIndex = hashedKey % hashPtr->numBuckets;
  printf("key %s hashes to bucket # %d\n", key, bucketIndex);
  Array* bucketPtr = valueAt(hashPtr->store, bucketIndex);

  return bucketPtr;
}

void add(HashMap* hashPtr, char* key, int value) {
  Array* bucketPtr = forEl(hashPtr, key);

  Array kvPair = makeArray();
  push(&kvPair, key);
  push(&kvPair, &value);

  push(bucketPtr, &kvPair);
}

int find(HashMap* hashPtr, char* key) {
  Array bucket = *forEl(hashPtr, key);
  unsigned long bucketSize = sizeof(bucket) / sizeof(Array*);
  int i;
  for (i = 0; i < bucketSize; i++) {
    printf("looking for key %s\n", key);
    Array* ptrToThisPair = (Array*) valueAt(bucket, i);

    printf("inspecting pair with address %p\n", ptrToThisPair);
    //printf("pair has %i elements\n",(int) sizeof(*ptrToThisPair) / sizeof(Array*));
    if (ptrToThisPair == '\0') { continue; }
    //char* thisKey = *(ptrToThisPair->store) + 1;
    //char* thisKey = (char*) valueAt(*ptrToThisPair, 0);
    //printf("inspecting key %s\n", thisKey);
/*
    if ((char*) *valueAt(*ptrToThisPair, 0) == key) {
      return (int) valueAt(*ptrToThisPair, 1);
    }*/
  }

  return 0;
}

int main() {
  HashMap myHash = makeHashMap();


  add(&myHash, "one", 1);
  add(&myHash, "two", 2);
  add(&myHash, "three", 3);

  int one = find(&myHash, "one");
  int two = find(&myHash, "two");
  //int three = find(&myHash, "three");

  printf("%d\n", one);

  return 0;
}
