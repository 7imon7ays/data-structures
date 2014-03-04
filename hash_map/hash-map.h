
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

static Array* _forEl(Array* storePtr, int (*hash)(void*), void* keyPtr) {
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

static void resizeHash(HashMap* hashPtr) {
  Array* oldStorePtr = &hashPtr->store;
  Array* newStorePtr = malloc(sizeof(Array));
  makeArray(newStorePtr);

  _makeBuckets(newStorePtr, oldStorePtr->storeSize * 2);

  int i;
  int numBuckets = oldStorePtr->storeSize;
  for (i = 0; i < numBuckets; i++) {
    Array* oldBucketPtr = (Array*) valueAt(oldStorePtr, i);
    int j;
    for (j = 0; j < oldBucketPtr->storeSize; j++) {
      KVPair* kvPairPtr = (KVPair*) valueAt(oldBucketPtr, j);
      Array* newBucketPtr = _forEl(newStorePtr, hashPtr->hash, kvPairPtr->keyPtr);
      push(newBucketPtr, kvPairPtr);
    }
  }

  hashPtr->store = *newStorePtr;
  //free(oldStorePtr); TODO: fix freeing
}

void add(HashMap* hashPtr, void* keyPtr, void* valuePtr) {
  if ( (float) hashPtr->numElems / hashPtr->store.storeSize >
      hashPtr->maxElemsPerBucket ) {
    resizeHash(hashPtr);
  }

  void* foundValuePtr = find(hashPtr, keyPtr);
  if (hashPtr->eq(valuePtr, foundValuePtr)) {
    return;
  }

  Array* bucketPtr = _forEl(&(hashPtr->store), hashPtr->hash, keyPtr);
  KVPair* kvPairPtr = malloc(sizeof(KVPair));
  kvPairPtr->keyPtr = keyPtr;
  kvPairPtr->valuePtr = valuePtr;

  push(bucketPtr, kvPairPtr);
  hashPtr->numElems++;
}
