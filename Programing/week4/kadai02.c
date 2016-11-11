#include <stdio.h>

int main() {
  char s[] = "12934875628476528734692734697263475629101234100";
  int count[10];
  int len = strlen(s); // 文字列sの長さ
  int i, n;

    for (i = 0; i < 10; i ++){
        count[i] = 0;
    }
  for (i = 0;i < len;i++) {   
    count[s[i] - '0'] += 1;
  }

  int is_even;
  for (n = 0;n <= 9;n++) {
    is_even = count[n] % 2;
    if(is_even == 0) {
      printf("%d is even\n", n);
    } else {
      printf("%d is odd\n", n);
    }
  }
  
  return 0;
}
