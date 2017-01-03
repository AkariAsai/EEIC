#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 70

int cell[HEIGHT][WIDTH];

void init_cells() {
  int i, j;

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = 0;
    }
  }

  cell[20][30] = 1;
  cell[22][30] = 1;
  cell[22][31] = 1;
  cell[23][31] = 1;
  cell[20][32] = 1;
}

// assignment 2
void init_cells_random() {
  int i, j, num;
  srand((unsigned)time(NULL));
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
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

// practice 課題
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

//@brief This is a method to count how many cells are still alive.
//@details This method walk though all of the value of cell (an array of int)
// and add values to sum.
int count_alive_cells() {
  int i, j, sum = 0;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      sum += cell[i][j];
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

  init_cells();
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
