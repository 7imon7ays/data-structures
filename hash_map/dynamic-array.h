typedef struct {
  int id;
  int storeSize;
  int storeLimit;
  void** store;
} Array;

void makeArray(Array* arrPtr) {
  arrPtr->storeSize = 0;
  arrPtr->storeLimit = 10;
  arrPtr->store = malloc(sizeof(void*) * arrPtr->storeLimit);
}

int* valueAt(Array* arrPtr, int index) {
  return *(arrPtr->store + index);
}

void copy(void** from, void** to, int numEls) {
  int i;
  for (i = 0; i < numEls; i++) {
    to[i] = from[i];
  }
}

void resize(Array* arrPtr) {
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

