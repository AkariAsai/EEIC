#include <stdio.h>
#include<math.h>

double series();

int main () {
  double pi;
  double s = series();
  pi =  sqrt(6 * s);
  printf("%f\n",pi );
  return 0;
}

double series() {
  double sum = 0;
  double denominator;
  for (int i = 1; i < 100; i ++) {
    denominator = i * i * pow(2,i - 1);
    sum += 1/denominator; 
  }
  return sum + pow(log(2), 2);
}
