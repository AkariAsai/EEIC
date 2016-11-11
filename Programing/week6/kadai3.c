#include <stdio.h>
#include <stdlib.h>
#define MAXCT 30000
double random_float(double, double);
double isIncluded(double x, double y);

int main()
{
    int seed;
    int k,ct=0;
    float x,y;
    
    scanf("%d",&seed); /* シードの入力 */
    printf("seed = %d\n",seed);
    srand(seed);       /* 乱数の初期化 */

    for (k = 0; k < MAXCT; k++){
      int x = random_float(0,1);
      int y = random_float(0,1);
      if (isIncluded(x, y)){
	ct++;
      }
    }
          printf("Approx. PI = %f\n",4.0*ct/MAXCT);
}

double random_float(double min, double max)
{
    return min + ((max-min)*rand())/RAND_MAX;
}

int isIncluded(double x, double y){
  return (((pow(x, 2) + pow(y, 2)) < 1);
}
