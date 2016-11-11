#include <stdlib.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 15

void init_matrix(char matrix[HEIGHT][WIDTH]);
void update_matrix(char matrix[HEIGHT][WIDTH]);
void draw_matrix(char matrix[HEIGHT][WIDTH]);

int main (){
  char matrix[HEIGHT][WIDTH];
  init_matrix(matrix);
  while (1){
    draw_matrix(matrix);
    update_matrix(matrix);
  }
}

void init_matrix(char matrix[HEIGHT][WIDTH]){
  int i, j;
  for (i = 0;i < HEIGHT;i ++){
    for (j = 0;j < WIDTH;j ++){
      matrix[i][j] = '.';
    }
  }
}

void update_matrix(char matrix[HEIGHT][WIDTH]){
  int r, w;
  char a;
  scanf("%d %d %c", &r, &w, &a);
  matrix[r][w] = a;
}

void draw_matrix(char matrix[HEIGHT][WIDTH]){
  int i, j;
  system("clear");
  for (i = 0;i < HEIGHT;i ++){
    for (j = 0;j < WIDTH;j ++){
      putchar(matrix[i][j]);
      putchar(' ');
    }
    putchar('\n');
  }
}
