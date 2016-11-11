#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define NALPHA 26

int main()
{
  FILE *fp;
  fp=fopen("news.txt","r");

  int count[NALPHA][NALPHA];
  double prob[NALPHA][NALPHA];
  double entropy[NALPHA];
  int c, i, j, sum; int first, second, minidx, maxidx;
  double min, max;

  for( i = 0 ; i < NALPHA ; i++ ) {
    entropy[i] = 0;
    for( j = 0 ; j < NALPHA ; j++ ) {
      count[i][j] = 0;
    }
  }

  second = ' ';
  while((c = fgetc(fp)) != EOF) {
    first = second;
    second = c;
    if(isalpha(first) && isalpha(second) ) {
      count[first-'a'][second-'a']++;
    }
  }

  for( i = 0 ; i < NALPHA ; i++ ) {
    sum = 0;

    double ent;
    for( j = 0 ; j < NALPHA ; j++ ) {
      sum += count[i][j];
    }
    for( j = 0 ; j < NALPHA ; j++ ) {
      if (count[i][j] != 0) {
      prob[i][j] = (double)count[i][j]/(double)sum;
      entropy[i] += prob[i][j]  * (-log2(prob[i][j]));
      }
    }
  }

  for( i = 0 ; i < NALPHA ; i++ ) {
    printf( "[%c]: ent = %e\n", 'a' + i, entropy[i]);
  }
  fclose(fp);
  return 0;
}
