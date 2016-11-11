#include <stdio.h>

int main(void)
{
  char str[] = "ABC";
  char str1[] = "ABC";
  char str2[] = "ABD";
  char str3[] = "B";
  char str4[] = "AAAA";

  printf("strcmp(%s, %s) = %d\n", str, str1, strcmp1(str, str1));
  printf("strcmp(%s, %s) = %d\n", str, str2, strcmp1(str, str2));
  printf("strcmp(%s, %s) = %d\n", str, str3, strcmp1(str, str3));
  printf("strcmp(%s, %s) = %d\n", str, str4, strcmp1(str, str4));

  return 0;
}

int strcmp1(char *s, char *t){
  for ( ; *s == *t; s++, t++){
    if (*s == '\0'){
      return 0;
    }
  }
  return *s - *t;
}
