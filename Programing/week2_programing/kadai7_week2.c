#include <stdio.h>

int gcd (int, int);

int main () {
  int r;
  int a = 8733;
  int b = 64681;
  r = gcd(a, b);
  printf("gcd(%d, %d) = %d\n", a, b, r);
  return 0;
}


int gcd(int a, int b){
  int max = 0;
    
  for (int i =1; i <= a && i <= b; i++)
    {
      if (a%i == 0 && b%i == 0){
	max = i;
      }
    }
  return max;
}
