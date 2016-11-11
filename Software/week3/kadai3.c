#include <stdio.h>
#include <math.h>

int main()
{
  for (int i = 0; i < 50; i++){
    double max = 20 * (sin(i * 3.14 * 0.1)) + 20;
    for (int j = 0; j < max; j++){
      printf(" ");
    }
    printf("*\n");
  }
  return 0;
}
