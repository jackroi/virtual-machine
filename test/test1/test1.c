#include <stdio.h>

int fact(int n) {
  int i;
  int res;

  res = 1;
  for (i = 2; i <= n; i++) {
    res *= i;
  }

  return res;
}

int main() {
  int r = fact(5);
  printf("%d\n", 5);

  return 0;
}
