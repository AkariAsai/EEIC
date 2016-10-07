#include <stdio.h>

typedef struct goldbach {
  int first;
  int second;
}goldbach;

int is_prime(int n);
goldbach get_gold_bach (int num, int prime_nums[]);

int main () {
  int prime_nums[500];
  int count = 0;
    
  //Initializes an array of prime nnumbers lower than 1000.
  for (int i = 2; i < 1000; i ++){
    if(is_prime(i)) {
      prime_nums[count] = i;
      count ++;
    }
  }
  //Walk though even numbers until 1000.
  for (int num = 2; num < 500; num++){
    goldbach result = get_gold_bach(num * 2, prime_nums);
    printf("%d = %d + %d\n", num * 2, result.first, result.second);
  }
  return 0;
}

int is_prime(int n){
  for (int i = 2; i < n; i ++){
    if (n % i == 0){
      return 0;
    }
  }
  return 1;
}

goldbach get_gold_bach (int num, int prime_nums[]) {
  goldbach result;
    
  for (int j = 0; j < 500; j++){
    for (int k = 0; k < 500; k++){
      if (prime_nums[j] + prime_nums[k] == num){
        result.first = prime_nums[j];
        result.second = prime_nums[k];
        return result;
      }
    }
  }
  return result;
}

