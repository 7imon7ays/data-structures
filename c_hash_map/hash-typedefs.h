typedef struct {
  Array store;
  int numElems;
  int maxElemsPerBucket;

  int (*eq)(void*, void*);
  int (*hash)(void*);
} HashMap;

int intEq(int* ip1, int* ip2) {
  return (*ip1 == *ip2 ? 1 : 0);
}

int intHash(int* ip1) {
  return SuperFastHash(ip1, sizeof(int));
}

typedef struct {
  int x;
  int y;
} Coordinate;

int coordinateEq(Coordinate* cp1, Coordinate* cp2) {
  return ((cp1->x == cp2->x) || (cp1->y == cp2->y)) ? 1 : 0;
}

int coordinateHash(Coordinate* cp1) {
  return SuperFastHash(cp1, sizeof(Coordinate));
}

int strEq(char* str1, char* str2) {
  return strcmp(str1, str2) == 0 ? 1 : 0;
}

int strHash(char* sp1) {
  int strLen = strlen(sp1);
  return SuperFastHash(sp1, strLen);
}
