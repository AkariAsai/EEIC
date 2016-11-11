#include<stdio.h>

void  strcpy1(char *s, char *t);

int main () {
  char ammessage[] = "now is he time";
  char *pmessage = "Hello world";
  printf("First String = %s, Second string = %s\n", ammessage, pmessage);
  strcpy1(ammessage, pmessage);
  printf("First String = %s, Second string = %s\n", ammessage, pmessage);
  return 0;
}

void strcpy1(char *s, char *t){
  while ((*s = *t) != '\0'){
    s++;
    t++;
  }
}
