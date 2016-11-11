#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 15

void init_matrix(char matrix[HEIGHT][WIDTH]);
void draw_matrix(char matrix[HEIGHT][WIDTH]);
void update_matrix(char matrix[HEIGHT][WIDTH], int count);

int main()
{
  int i, j;
  char matrix[HEIGHT][WIDTH];

  init_matrix(matrix);
  int count  = 0;
  for(;;){
    update_matrix(matrix, count);
    draw_matrix(matrix);
    sleep(1);
    count++;
  }
  return 0;
}

void update_matrix(char matrix[HEIGHT][WIDTH], int count){
  int i, j;
  for (i = 0;i < HEIGHT;i ++){
    for (j = 0;j < WIDTH;j ++){
      if (i == count && j == count){
	matrix[i][j] = '*';
      }
    }
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
