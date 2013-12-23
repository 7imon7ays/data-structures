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

  for (i = 0; i < hashMap.numBuckets; i++) {
    Array newBucket = makeArray();
    push(&hashMap.store, &newBucket);
  }
}

HashMap makeHashMap() {
  HashMap newHashMap;
  newHashMap.numBuckets = 10;
  makeBuckets(&newHashMap);
  newHashMap.numElems = 0;

  return newHashMap;
}

// manipulation

Array forEl(HashMap* hashPtr, char* key) {
  int len;
  for (len = 0; key[len] != '\0'; len++) {}
  uint32_t hashedValue = SuperFastHash(key, len);
  int bucketIndex = hashedValue % hashPtr->numBuckets;
  Array bucket = *(&hashPtr->store + bucketIndex * sizeof(void*));

  return bucket;
}

void add(HashMap* hashPtr, char* key, int value) {
  Array bucket = forEl(hashPtr, key);
  void* kvPair[2];
  kvPair[0] = key;
  kvPair[1] = &value;
  push(&bucket, kvPair);
}

int find(HashMap* hashPtr, char* key) {
  Array bucket = forEl(hashPtr, key);
  unsigned long bucketSize = sizeof(bucket) / sizeof(int);
  int i;
  for (i = 0; i < bucketSize; i++) {
    void* thisPair = (&bucket + i);
    if ((char*) thisPair == key) {
      return (int) thisPair + 1;
    }
  }

  return 0;
}

int main() {
  HashMap myHash = makeHashMap();

  add(&myHash, "one", 1);
  add(&myHash, "two", 2);
  add(&myHash, "three", 3);

  int value = find(&myHash, "two");

  printf("%d\n", value);

  return 0;
}
