#include <stdio.h>

int is_prime (int);

int main(){
  int i;
  for (i = 2; i <= 1000; i ++){
    if(is_prime(i)==1) {
      printf("%d is prime\n", i);
    }
  }
}

int is_prime(int n){
  for (int i = 2; i < n; i ++){
    if (n % i == 0){
      return 0;
    }
  }
  return 1;
}
