#include <stdio.h>

int sum(int x, int y) {
  return (int)(x+y);
}

int main(void) {
  int a, b, c;

  a = 3;
  b = 2;

  c = sum(a, b);

  printf("The sum of a + b = %d + %d = %d\n", a, b, c);

  return 0;
}