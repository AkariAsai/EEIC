#include <stdio.h>

int main (){
  int *i, *sum;
  int i0, sum0;
  sum0 = 0;
  i = &i0;
  sum = &sum0;

  for (*i= 0; *i <= 10; (*i)++){
    *sum = *sum + *i;
  }

  printf("sum = %d\n", *sum);

  return 0;
}
