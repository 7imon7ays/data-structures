typedef int (*comp_func)(void*, void*);

int ascending(void* aPtr, void* bPtr);

int descending(void* aPtr, void* bPtr);

void quickSort(
      void* array[], const int len, int comp_given, ...);

