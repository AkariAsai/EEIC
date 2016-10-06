#include <stdio.h>

int main () {
  int c;
  while((c = getchar())!= EOF) {
    if (c == ' '){
      while((c = getchar())!= EOF) {
	if (c == '\n'){
	  break;
	}
      }
    }
    putchar(c);
  }
  return 0;
}
