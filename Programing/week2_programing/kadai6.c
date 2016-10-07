#include <stdio.h>
#include<math.h>

int is_prime (int);
double series();

int main () {
  double pi;
  double s = series();
  pi =  sqrt(6/s);
  printf("pi = %f\n",pi );
  return 0;
}

double series() {
  double sum = 1;
  for (int i = 1; i < 10000; i ++) {
    if (is_prime(i)){
      sum *= 1 - 1/pow(i, 2);
    }
  }
  return sum + pow(log(2), 2);
}

int is_prime(int n){
  for (int i = 2; i < n; i ++){
    if (n % i == 0){
      return 0;
    }
  }
  return 1;
}
