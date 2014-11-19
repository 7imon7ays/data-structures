void qsort(int array[], const int len);
static void qsortStep(int array[], const int left, const int right);
static void swap(int arr[], const int i, const int j);

void qsort(int array[], const int len) {
  qsortStep(array, 0, len - 1);
}

static void qsortStep(int array[], const int left, const int right) {
  int pivot_idx, num_smaller, i, right_partition;

  // left is greater than right when there are two
  // els remaining and left starts at "partition + 1"
  if (left >= right) {
    return;
  }

  pivot_idx = (left + right) / 2;
  // move pivot to left-most index so comparisons
  // to remaining elements are sequential
  swap(array, left, pivot_idx);
  // right partition separates pivot's smaller
  // els from pivot's greater els
  right_partition = left;

  for (i = left + 1; i <= right; i++) {
    if (array[left] > array[i]) {
      swap(array, ++right_partition, i);
    }
  }

  swap(array, left, right_partition);
  qsortStep(array, left, right_partition - 1);
  qsortStep(array, right_partition + 1, right);
}

static void swap(int arr[], int i, int j) {
  const int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

