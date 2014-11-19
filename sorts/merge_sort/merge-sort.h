#include <stdlib.h>

static int getRightLength(int len) {
  int rightLen;
  if (len % 2 == 0) {
    rightLen = len / 2;
  } else {
    rightLen = len / 2 + 1;
  }

  return rightLen;
}

static void split(int source[], int length, int left[], int right[]) {
  int i;
  int middle = length / 2;

  for (i = 0; i < middle; i++) {
    left[i] = source[i];
    right[i] = source[middle + i];
  }

  if (length % 2 != 0) {
    right[i] = source[middle + i];
  }
}

static int* merge(int* left, int leftLen, int* right, int rightLen) {
  int mergeLength = leftLen + rightLen;
  int* merged = malloc(mergeLength * sizeof(int));

  int l = 0;
  int r = 0;
  int i;
  int leftLessThanRight;
  int endOfRight;

  for (i = 0; i < mergeLength; i++) {
    leftLessThanRight = left[l] < right[r];
    endOfRight = r >= rightLen;

    if (l < leftLen && ( leftLessThanRight || endOfRight )) {
      merged[i] = left[l];
      l++;
    } else if (r < rightLen) {
      merged[i] = right[r];
      r++;
    }
  }

  return merged;
}

int* mergeSort(int nums[], int len) {

  if (len < 2) {

    return nums;

  } else {

  int leftLen = len / 2;
  int rightLen = getRightLength(len);
  int left[leftLen];
  int right[rightLen];

  split(nums, len, left, right);

  int* sortedLeft = mergeSort(left, leftLen);
  int* sortedRight = mergeSort(right, rightLen);

  int* merged = merge(sortedLeft, leftLen, sortedRight, rightLen);
  return merged;
  }
}

