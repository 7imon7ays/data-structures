typedef struct {
  int storeSize;
  int storeLimit;
  void** store;
} Array;

typedef struct {
  void* keyPtr;
  void* valuePtr;
} KVPair;

void makeArray(Array* arrPtr) {
  arrPtr->storeSize = 0;
  arrPtr->storeLimit = 10;
  arrPtr->store = malloc(sizeof(void*) * arrPtr->storeLimit);
}

void* valueAt(Array* arrPtr, int index) {
  return *(arrPtr->store + index);
}

static void copy(void** from, void** to, int numEls) {
  int i;
  for (i = 0; i < numEls; i++) {
    to[i] = from[i];
  }
}

static void resize(Array* arrPtr) {
  int oldStoreLimit = arrPtr->storeLimit;
  void** newStore = (void**) malloc(sizeof(void*) * oldStoreLimit * 2);
  copy(arrPtr->store, newStore, oldStoreLimit);
  arrPtr->storeLimit = oldStoreLimit * 2;
  free(arrPtr->store);
  arrPtr->store = newStore;
}


void push(Array* arrPtr, void* valuePtr) {
  if (arrPtr->storeSize + 1 > arrPtr->storeLimit) {
    resize(arrPtr);
  }

  arrPtr->store[arrPtr->storeSize] = valuePtr;
  arrPtr->storeSize++;
  assert( arrPtr->storeSize <= arrPtr->storeLimit);
}

void freeArray(Array* arrPtr) {
  int i;
  for (i = 0; i < arrPtr->storeSize; i++) {
    void* thisElPtr = valueAt(arrPtr, i);
    if ( sizeof(*thisElPtr) == sizeof(Array) ) {
      freeArray(thisElPtr);
    } else {
      free(thisElPtr);
    }
  }
  free(arrPtr);
}

