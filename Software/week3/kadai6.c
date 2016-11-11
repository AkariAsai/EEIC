#include <stdio.h>
#include <ctype.h>

#define NALPHA 26


int main()
{
  FILE *fp;
  fp=fopen("news.txt","r");

  int count[NALPHA];
  int c, i;
  for (i = 0; i < NALPHA; i++){
    count[i] = 0;
  }

  while ((c = fgetc(fp)) != EOF){
    if (isalpha(c)){
      count[c-'a']++;
    }
  }

  for( i = 0 ; i < NALPHA ; i++ ) { 
    printf( "%c : %d\n", 'a'+i, count[i] );  
  }
  
  fclose(fp);
  return 0;
}
