#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define NALPHA 26

int main()
{
  FILE *fp;
  fp=fopen("news.txt","r");

  int sum_of_characters = 0;
  int count[NALPHA];
  int c, i;

  for (i = 0; i < NALPHA; i++){
    count[i] = 0;
  }

  while ((c = fgetc(fp)) != EOF){
    if (isalpha(c)){
      count[c-'a']++;
      sum_of_characters++;
    }
  }

  double en = 0;
  double prob;
  for( i = 0 ; i < NALPHA ; i++ ) {
    prob = (double)count[i]/(double)sum_of_characters;
    en += prob * (-log2(prob));
  }
  printf("entropy = %f\n", en);
  fclose(fp);

  return 0;
}
