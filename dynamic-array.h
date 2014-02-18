typedef struct {
  int storeSize;
  int storeLimit;
  char** store;
} Array;

static Array makeArray() {
  Array arr;
  arr.storeSize = 0;
  arr.storeLimit = 10;
  arr.store = malloc(sizeof(char*) * 5);
  return arr;
}

char* valueAt(Array arr, int index) {
  return *(arr.store + index);
}

void copy(char** from, char** to) {
  int i;
  unsigned long arrSize = sizeof(from) / sizeof(int);
  for (i = 0; i < arrSize; i++) {
    to[i] = from[i];
  }
}

void resize(Array* arrPtr) {
  arrPtr->storeLimit = arrPtr->storeLimit * 2;
  char** newStore = malloc(sizeof(char*) * arrPtr->storeLimit);
  copy(arrPtr->store, newStore);
  free(arrPtr->store);
  arrPtr->store = newStore;
}


char* push(Array* arrPtr, char* string) {
  if (arrPtr->storeSize + 1 > arrPtr->storeLimit) {
    resize(arrPtr);
  }

  arrPtr->store[arrPtr->storeSize] = string;
  arrPtr->storeSize++;

  return string;
}

