#include <stdio.h>
#include <stdlib.h>

void factor(int);
int main () {
  int n = 123456789;
  printf("Prime factor of %d\n", n);
  printf("%d = ", n);
  factor(n);
}

void factor(int n) {
  if (n == 1){
    return;
  } else {
    int num = 1;

    for (int i = 2; i <= n; i++){
      if (n % i == 0){
        if (i == n){
          printf("%d\n", i);
        }
        printf("%d * ", i);
        num = i;
        break;
      }
    }
    factor(n/num);
  }
}
