#include <stdio.h>

double pie( double x0, int N );

int main(){
  double x0 = 0.1;
  for (int i; i < 100; i++){
    printf("N: %d %f\n", i, pie(x0, i));
  }
  return 0;
}

double pie( double x0, int N ){
  for (int i; i< N;i++){
    if (x0 <= 0.5){
      x0 = 2 * x0;
    } else {
      x0 = 2 - 2*x0;
    }
  }
  return x0;
}

