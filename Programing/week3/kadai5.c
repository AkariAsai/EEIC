#include <stdio.h>
#include <stdlib.h>

int mod_apm(int a, int p, int m);

int main (){
  int a0 = 541;
  int p0 = 1234;
  int m0 = 1299709;
  printf("%d ^ %d mod %d is %d\n", a0, p0, m0, mod_apm(a0, p0, m0));
  
}

int mod_apm(int a, int p, int m){
  if (p == 1){
    return a % m;
  } else {
    return a * mod_apm(a, p-1, m) % m;
  } 
}

