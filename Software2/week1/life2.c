#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 70

int cell[HEIGHT][WIDTH];

//@brief This is a method to initialize cells randomly.
//@details In this method, I use rand() function and it returns a num among 0 -
// 9. Only when the num is zero (It should be around 10%), the value of each
// cell will be modified.
void init_cells_random() {
  int i, j, num;
  srand((unsigned)time(NULL));
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = 0;
      num = rand() % 10;
      if (num == 0) {
        cell[i][j] = 1;
      }
    }
  }
}

void print_cells(FILE *fp) {
  int i, j;

  fprintf(fp, "----------\n");

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      const char c = (cell[i][j] == 1) ? '#' : ' ';
      fputc(c, fp);
    }
    fputc('\n', fp);
  }
  fflush(fp);

  sleep(1);
}

int count_adjacent_cells(int i, int j) {
  int n = 0;
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      n += cell[k][l];
    }
  }
  return n;
}

int isAlive(int sum, int current) {
  switch (sum) {
  case 2:
    return current ? 1 : 0;
  case 3:
    return 1;
  default:
    return 0;
  }
}

void update_cells() {
  int i, j;
  int cell_next[HEIGHT][WIDTH];

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell_next[i][j] = 0;
      const int n = count_adjacent_cells(i, j);
      if (isAlive(n, cell[i][j])) {
        cell_next[i][j] = 1;
      }
    }
  }

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = cell_next[i][j];
    }
  }
}

int count_alive_cells() {
  int i, j, sum = 0;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      if (cell[i][j]) {
        sum++;
      }
    }
  }
  return sum;
}

int main() {
  int gen;
  FILE *fp;

  if ((fp = fopen("cells.txt", "a")) == NULL) {
    fprintf(stderr, "error: cannot open a file.\n");
    return 1;
  }

  // The answer for question 1.
  init_cells_random();
  print_cells(fp);

  for (gen = 1;; gen++) {
    printf("generation = %d\n", gen);
    printf("%d cells are alives.\n", count_alive_cells());
    update_cells();
    print_cells(fp);
  }
  fclose(fp);

  return 0;
}
