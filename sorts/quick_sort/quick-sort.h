void quickSort(
      void* array[], const int len,
      int (*comp)(void*, void*)
    );

static void quickSortStep(
      void* array[], const int left, const int right,
      int (*comp)(void*, void*)
    );

static void _swap(void* arr[], const int i, const int j);

void quickSort(void* array[], const int len,
      int (*comp)(void*, void*)
    ) {

  quickSortStep(array, 0, len - 1,
      (int (*)(void*, void*))comp
    );
}

static void quickSortStep(void* array[], const int left, const int right,
      int (*comp)(void*, void*)
    ) {
  int pivot_idx, num_smaller, i, right_partition;

  // left is greater than right when there are two
  // els remaining and left starts at "partition + 1"
  if (left >= right) {
    return;
  }

  pivot_idx = (left + right) / 2;
  // move pivot to left-most index so comparisons
  // to remaining elements are sequential
  _swap(array, left, pivot_idx);
  // right partition separates pivot's smaller
  // els from pivot's greater els
  right_partition = left;

  for (i = left + 1; i <= right; i++) {
    if (comp(array[left], array[i])) {
      _swap(array, ++right_partition, i);
    }
  }

  _swap(array, left, right_partition);

  quickSortStep(
      array, left, right_partition - 1,
      (int (*)(void*, void*)) comp
    );
  quickSortStep(
      array, right_partition + 1, right,
      (int (*)(void*, void*)) comp
    );
}

static void _swap(void* arr[], int i, int j) {
  void* temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

