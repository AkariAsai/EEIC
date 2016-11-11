#include<stdio.h>
#include<string.h>

void reverse(char *s);

int main (){
  char s[] = "hello";
  reverse(s);
  printf("%s\n", s);
  return 0;
}

void reverse(char *s){
  char new_s[100];
  strcpy(new_s, s);
  for (int i = 0; i < strlen(s); s++){
    *s = new_s[strlen(s) - i - 1];
  }
}

