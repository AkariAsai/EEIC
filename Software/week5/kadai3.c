#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 30
#define HEIGHT 15

void init_matrix(char matrix[HEIGHT][WIDTH]);
void load_matrix(char matrix[HEIGHT][WIDTH]);
void update_matrix(char matrix[HEIGHT][WIDTH]);
void draw_matrix(char matrix[HEIGHT][WIDTH]);
void save_matrix(char matrix[HEIGHT][WIDTH]);

int main()
{
  char matrix[HEIGHT][WIDTH];
  int x, y;
  init_matrix(matrix);
  while (1){
    load_matrix(matrix);
    draw_matrix(matrix);
    update_matrix(matrix);
    save_matrix(matrix);
  }
  return 0;
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

void load_matrix(char matrix[HEIGHT][WIDTH]){
  int i,j;
  char c;
  FILE *fp;
  fp= fopen("data.txt", "r");
  for (int i = 0;i < HEIGHT;i ++){
    for ( int j = 0;j < WIDTH;j ++){
      c = fgetc(fp);
	matrix[i][j] = c;
    }
  }
  fclose(fp);
}

void save_matrix(char matrix[HEIGHT][WIDTH]){
  FILE *fp;
  fp= fopen("data.txt", "w");
  for (int i = 0;i < HEIGHT;i ++){
    for ( int j = 0;j < WIDTH;j ++){
      fputc(matrix[i][j],fp);
    }
    putchar('\n');
  }
  fputc('\n', fp);
  fclose(fp);
}


