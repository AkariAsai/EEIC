#include <stdio.h>

int gcd (int, int);

int main () {
  int a, b, c;
  
  for (c =1; c < 1000; c++){
    for (b = 1; b < c; b++){
      for (a = 1; a < b; a++){
	if (a * a + b * b == c * c && gcd(a, b) == 1){
	  printf("%d ^ 2+  %d ^ 2 = %d ^ 2\n", a, b, c);
                    
	}
      }
    } 
  }
  return 0;
}


int gcd(int a, int b){
  int max = 1;
  
  for (int i =1; i <= a && i <= b; i++){
    if (a%i == 0 && b%i == 0){
      max = i;
    }
  }
  return max;
}
