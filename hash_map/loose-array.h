typedef struct {
  int storeSize;
  int storeLimit;
  void** store;
} Array;

Array makeArray() {
  Array arr;
  arr.storeSize = 0;
  arr.storeLimit = 10;
  arr.store = malloc(sizeof(void*) * 5);
  return arr;
}

void* valueAt(Array arr, int index) {
  return *(arr.store + index);
}

void copy(void** from, void** to) {
  int i;
  unsigned long arrSize = sizeof(from) / sizeof(int);
  for (i = 0; i < arrSize; i++) {
    to[i] = from[i];
  }
}

void resize(Array* arrPtr) {
  arrPtr->storeLimit = arrPtr->storeLimit * 2;
  void* newStore = malloc(sizeof(void*) * arrPtr->storeLimit);
  copy(arrPtr->store, newStore);
  free(arrPtr->store);
  arrPtr->store = newStore;
}


void push(Array* arrPtr, void* valuePtr) {
  printf("pushing value %d\n",
      valuePtr + 1 * sizeof(void*));
  if (arrPtr->storeSize + 1 > arrPtr->storeLimit) {
    printf("array resizing because store size is ");
    printf("%d, and store limit is %d.\n",
        arrPtr->storeSize, arrPtr->storeLimit);
    resize(arrPtr);
  }

  arrPtr->store[arrPtr->storeSize] = valuePtr;
  arrPtr->storeSize++;

  return *valuePtr;
}

