#include <stdio.h>

int main() {
  int n = 158340421;
  int min = 1;
  int max = 1000;
  int mid;
  while (min <= max){
    mid = (min + max)/2;
    if (mid * mid * mid < n){
      min = mid;
    } else if (mid * mid * mid > n){
      max = mid;
    } else {
      printf("%d\n", mid);
      break;
    }

  }
  return 0;
}
