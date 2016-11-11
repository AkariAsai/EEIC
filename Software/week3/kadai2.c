#include <stdio.h>

int main () {
  int c;
  int isterminated = 0;

  while((c = getchar()) != EOF || !isterminated){
    switch (c) {
    case 'g':
    case 'G':
      printf("あなたはグーをだしました。わたしはチョキをだしました。あなたの勝ち！");
      break;
    case 'c':
    case 'C':
      printf("あなたはチョキをだしました。わたしはグーをだしました。あなたの勝ち！");
      break;
    case 'p':
    case 'P':
      printf("あなたはパーをだしました。わたしはグーをだしました。あなたの勝ち！");
      break;
    case 'q':
    case'Q':
      isterminated = 1;
      break;
    default:
      break;
    }
  }
}
