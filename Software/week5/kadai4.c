#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define WIDTH 30
#define HEIGHT 15
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
  save_matrix(matrix);
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
  printf("This is load date");
  int i,j, index, count;
  char c;
  FILE *fp;
  char data[1000];
  fp= fopen("data2.txt", "r");

  index = 0;
  while ((c = fgetc(fp)) !=EOF){
    count = c - '0';
    c =  fgetc(fp);
    printf("%c, %d\n", c, count);
    for (i = 0; i < count; i++){
      data[index] = c;
      index++;
    }
  }
  index = 0;
  for (int i = 0;i < HEIGHT;i ++){
    for ( int j = 0;j < WIDTH;j ++){
      matrix[i][j] =(char)data[index];
      index++;
    }
  }
  fclose(fp);
}

void save_matrix(char matrix[HEIGHT][WIDTH]){
  FILE *fp;
  int i, j;
  char prev = '\0';
  char c;
  int count = 0;
  fp= fopen("data2.txt", "w");
  printf("This is saving");
  
  for (int i = 0;i < HEIGHT;i ++){
    for (int j = 0;j < WIDTH;j ++){
      c = matrix[i][j];
      if (c != prev){
	count++;
	while (count >= 1){
	  int repeat_time = MIN(count, 9);
	  printf("%d, %c\n", repeat_time, prev);
	  fputc('0' + repeat_time, fp);
	  fputc(prev, fp);
	  count -= repeat_time;
	}
	prev = c;
	count = 0;	
      } else {
	count++;
      }
    }
  }
  //For the last repeated character.
  while (count > 1){
    int repeat_time = MIN(count, 9);
    fputc('0' + repeat_time, fp);
    fputc(prev, fp);
    count -= repeat_time;
    prev = c;
  }
  fputc('\n', fp);
  fclose(fp);
}


