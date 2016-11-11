#include<stdio.h>

int is_three_included(int n);

int main() {
  for (int i = 1; i < 1000; i++){
    if (i % 3 == 0 || is_three_included(i)) {
      printf("%d!!!\n", i);
    } else {
      printf("%d\n", i);
    }
  }
  return 0;
}

int is_three_included(int n){
  while (n > 0){
    if (n % 10 == 3){
      return 1;
    }
    n = n / 10;
  }
  return 0;
}
