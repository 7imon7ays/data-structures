#include "dynamic-array.h"

int main() {
  Array topArray = makeArray();
  Array subArray = makeArray();

  push(&topArray, &subArray);
  push(&subArray, "hello");
  int one = 1;
  push(&topArray, &one);

  Array* retrievedArr = valueAt(topArray, 0);
  char* retrievedStr = valueAt(*retrievedArr, 0);
  int retrievedInt = *valueAt(topArray, 1);

  printf("%s\n", retrievedStr);
  printf("%d\n", retrievedInt);


  return 0;
}
