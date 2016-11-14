#include <stdio.h>
#include <stdlib.h>

void question6(int num);
void question5();
void question8();
int main() {

  //question2
  int i=5;
  printf("%d\n", i==5);//output:1, ここで==は比較演算子。つまり「iが５」ならば1(true)をかえし、ちがえば0をかえす。

  //question3
  int *a, b=10;
  a = &b;
  printf("%d\n", *a);

  //question4
  printf("%c\n", ("hello"[1]-1));//output:d
  //question6
  int num1 = 24;
  int num2 = 13;
  question6(num1);
  question6(num2);
  question5();
  question8();

  return 0;
}


void question6(int num) {
  //check primeNumber
  for (int i = 2; i < num; i++){
    if (num % i == 0){
      printf("%d is not a prime number.\n", num);
      return;
    }
    }
    printf("%d is a prime number.\n", num);

}

void question5(){
  char *array[5] = {"apple", "melon", "orange", "banana", "kiwi"};
  printf("%s\n", &array[3][0] + 5);//array[3] + 5もOkay
}

void question8(){
  int appeared[101];
  int i;
  for (i = 0; i < 101; i++){
    appeared[i] = 0;
  }
  int seed = 0;
  while (1){
    srand(seed);
    for (int i = 0; i < 1000; i++){
      int randNum = rand()%20 + 1;
      if (appeared[randNum] == 0){
        appeared[randNum] = 1;
      }
      }
      int sum = 0;
      for (i = 0; i < 101; i++){
        sum += appeared[i];
      }
      if (sum > 20){
        seed++;
        printf("it takes %d times.", seed);
                return;
      } else {
        seed++;
        sum = 0;
      }
    }
    }
