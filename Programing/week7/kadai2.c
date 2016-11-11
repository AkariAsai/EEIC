#include <stdio.h>

int main(int argc, char** argv){
  char *fileName = argv[1];
  FILE *fp, *fp2;

  fp = fopen(fileName, "r");
  fp2 = fopen("sentence2.txt", "w");
  if (fp == NULL){
    printf("Failed to open the file\n");
    return 1;
  }

  char prev = '.';
  char c;
  while((c=getc(fp)) != EOF){
    if (c != ' '){
      if (prev == '.'){
	c = c - 32;
	prev = c;
      } else {
	prev = c;
      }
      putc(c, fp2);
    }
    else {
      putc(' ', fp2);
    }
  }
  return 1;
  
}


  
  
