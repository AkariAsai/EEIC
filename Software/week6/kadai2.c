#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void printRandNumWithSeed(int seed);

int main(int argc, char** argv)
{
  int seed = atoi(argv[1]);
    printRandNumWithSeed(seed);
    
    
  return 0;
}

void printRandNum() {
  //this method for assignment 2-1
  int i;
  srand((unsigned) time(NULL));

  for (i=1; i<=10; i++) {
    printf("%3d\n ",rand()%1000+1);
  }
}

void printRandNumWithSeed(int seed) {
  //this method for assignment 2-1
  int i;
  srand(seed);

  for (i=1; i<=10; i++) {
    printf("%3d\n ",rand()%1000+1);
  }
}

