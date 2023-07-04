#include <stdio.h>

// Every type is either _object_ or _function_
// Also, pointers = address; derived from reference type
// Object and function pointers are different

void swap(int, int); // defined in a minute

int main(void) {
  int a = 21;
  int b = 17;

  swap(a, b);
  printf("main: a = %d, b = %d\n", a, b);
  return 0;
}
// p. 15
