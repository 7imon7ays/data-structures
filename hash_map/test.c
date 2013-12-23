#include <stdio.h>
#include <stdlib.h>
#include "int-array.h"

int main() {
  Array arr = makeArray();
  Array subArr = makeArray();
  int value = 1;
  push(&subArr, &value);
  push(&arr, &subArr);
  Array* subArrPtr = valueAt(arr, 0);

  int otherValue = 2;
  push(subArrPtr, &otherValue);
  int* value2 = valueAt(*subArrPtr, 1);

  printf("%d\n", *value2);

  return 0;
}
