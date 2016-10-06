#include <stdio.h>

int main () {
  int x;
  int ct = 1;
  while ((x = getchar())!= EOF){
    if (ct % 2 == 0){
      putchar(x);
    }
    ct ++;
  }
  return 0;
}
