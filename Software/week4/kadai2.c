#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int *p;
  p = (int *) malloc(sizeof(int));
  *p = 100;
  printf("*p = %d\n", *p);
  printf("p = %p\n", p);
  printf("&p = %p\n", &p);
  return 0;
}

