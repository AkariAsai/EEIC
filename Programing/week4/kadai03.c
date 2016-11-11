#include <stdio.h>
/*
0から0.1刻みで，100までの和を計算するプログラム
*/
int main() {
  double sum = 0.0;
  double v = 0.0;
  while(v <= 100.0) {
    sum += v;
    v += 0.1;
  }

  printf("Sum is %f\n", sum);
  return 0;
}
