void qsort(int array[], int len);
void qsortStep(int array[], int left, int right);
void swap(int arr[], int i, int j);

void qsort(int array[], int len) {
  qsortStep(array, 0, len - 1);
}

void qsortStep(int array[], int left, int right) {
  int pivot_idx, num_smaller, i, right_partition;

  // left is greater than right when there are two
  // els remaining and left starts at "partition + 1"
  if (left >= right) {
    return;
  }

  pivot_idx = (left + right) / 2;
  // move pivot to left-most index so comparisons
  // to remaing elements are sequential
  swap(array, left, pivot_idx);
  num_smaller = 0;

  for (i = left + 1; i <= right; i++) {
    if (array[left] > array[i]) {
      num_smaller++;
      swap(array, left + num_smaller, i);
    }
  }

  // right partition separates pivot's smaller
  // els from pivot's greater els
  right_partition = left + num_smaller;
  swap(array, left, right_partition);
  qsortStep(array, left, right_partition - 1);
  qsortStep(array, right_partition + 1, right);
}

void swap(int arr[], int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

